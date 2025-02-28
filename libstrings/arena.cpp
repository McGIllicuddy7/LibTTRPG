
#include "arena.hpp"
constexpr size_t  ARENA_SIZE = 4096*8;
Arena::Arena(){
	m_next = 0;	
	m_buffer = new char[ARENA_SIZE];
	m_alloc_offset= 0;
	m_buffer_len = ARENA_SIZE;	
	m_delete_queue = 0;
}
Arena::Arena(size_t min_size){
	if (min_size %4096 != 0){
		min_size += 4096-min_size%4096;
	}
	m_next =0;
	m_buffer = new char[min_size];
	m_alloc_offset = 0;
	m_buffer_len =min_size;
	m_delete_queue = 0;
}
char *Arena::alloc_bytes(size_t size){
	if(size%16 != 0){
		size += 16-size%16;
	}
	m_lock.lock();
	if(m_alloc_offset+size>= m_buffer_len){
		if (m_next){
			m_lock.unlock();
			return m_next->alloc_bytes(size);
		} else{
			m_next = new Arena(size);
			m_lock.unlock();
			return m_next->alloc_bytes(size);
		}	
	}
	else{
		char * out = m_buffer+m_alloc_offset;
		m_alloc_offset += size;
		m_lock.unlock();
		return out;
	}	
}

Arena::~Arena(){
	m_lock.lock();
	while(m_delete_queue){
		(m_delete_queue->m_function)(m_delete_queue->m_ptr);
		Deleter *next = m_delete_queue->m_next;
		m_delete_queue->~Deleter();
		m_delete_queue = next;
	}
	delete []m_buffer;
	delete m_next;
	m_buffer =0;
	m_delete_queue =0;
	m_alloc_offset =0;
	m_buffer_len =0;
}
