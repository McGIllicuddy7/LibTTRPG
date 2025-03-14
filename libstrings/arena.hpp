#pragma once
#include <cstdint>
#include <cstdlib>
#include <assert.h>
#include <vector>
#include <new>
#include <functional>
#include <mutex>
#include <string>
#include <memory>
//Unowned view into memory 
template <typename T> struct Slice{
	T * m_start;
	size_t m_len;
	Slice(){
		m_start =0;
		m_len =0;
	}
	Slice(T * ptr, size_t len){
		m_start =ptr;
		m_len = len;
	}
	T * begin()const {
		return m_start;
	}
	T * end()const {
		return m_start+m_len;
	}
	T& operator[](size_t index){
		assert(index<m_len);
		return *(m_start+index);
	}
};
template <typename T>struct RefSlice{
	std::shared_ptr<T[]> m_ptr;
	size_t m_size;
	RefSlice(std::shared_ptr<T[]> ptr, size_t size){
		m_ptr = ptr;
		m_size = size;
	}
	static RefSlice<T> make(size_t count){
		std::shared_ptr<T[]> ptr = std::make_shared<T[]>(count);
		return RefSlice(ptr, count);
	}
	T& operator[](size_t idx){
		return m_ptr[idx];
	}
	const T& operator[](size_t idx)const{
		return m_ptr[idx];
	}
	size_t size()const {
		return m_size;
	}
	T* begin(){
		return m_ptr.get();
	}
	T* end(){
		return m_ptr.get()+m_size;
	}
};

class Deletable{
	public:
	size_t value;
	inline Deletable(){
		printf("created, 0\n");
		value = 0;
	}
	inline Deletable(Deletable & other){
		printf("copied, %zu\n", other.value);
		value = other.value;
	}
	inline Deletable(size_t ivalue){
		value = ivalue;
		printf("created, %zu\n",value) ;
	}
	inline Deletable & operator =(Deletable & other){
		printf("assigned %zu to %zu\n", value, other.value);
		value = other.value;
		return *this;
	}
	inline ~Deletable(){
		printf("deleted %zu\n", value);
	}

};
class Arena{
	struct Deleter{
		std::function<void(void *)> m_function;
		void * m_ptr;
		Deleter * m_next;
	};
	std::mutex m_lock;
	Arena * m_next;
	char * m_buffer;
	size_t m_alloc_offset;
	size_t m_buffer_len;
	Deleter * m_delete_queue;
	public:
	Arena();
	Arena(size_t min_size);
	Arena(Arena &) = delete;
	Arena(Arena &&) = delete;
	Arena & operator=(Arena &) = delete;
	Arena & operator=(Arena &&) = delete;
	~Arena();
	char * alloc_bytes(size_t size);
	template <typename T,typename...Args> T* alloc(Args...args){
		void * backing = (void*)alloc_bytes(sizeof(T));
		T * out = new (backing )T (args...);
		if constexpr (std::is_trivially_destructible<T>()){
			return out;
		} else{
			Deleter* del = (Deleter *)alloc_bytes(sizeof(Deleter));
			del->m_function = (std::function<void(void*)>)[](void * ptr){
				T * obj = (T*)ptr;
				obj->~T();
			};
			del->m_ptr = out;
			m_lock.lock();
			del->m_next = m_delete_queue;
			m_delete_queue = del;
			m_lock.unlock();
			return out;
		}
	}
	template <typename T> Slice<T> alloc_array(size_t count){	
		void * backing = (void*)alloc_bytes(sizeof(T));
		T * out = (T*)backing;
		for(size_t i =0; i<count; i++){
			new (out +i) T ();
		}
		if constexpr (std::is_trivially_destructible<T>()){
			return Slice<T>(out, count);
		} else{
			Deleter* del = (Deleter *)alloc_bytes(sizeof(Deleter));
			del->m_function = (std::function<void(void*)>)[count](void * ptr){
				T * obj = (T*)ptr;
				for(size_t i =0; i<count; i++){
					(obj+i)->~T();
				}			
			};
			del->m_ptr = out;
			m_lock.lock();
			del->m_next = m_delete_queue;
			m_delete_queue = del;
			m_lock.unlock();
			return Slice<T>(out,count);
		}
	}
};
