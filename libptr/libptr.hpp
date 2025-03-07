#pragma once 
#include <typeinfo>
namespace utils{
    template<typename T> class ClonableWrapper{
        public:
        virtual ClonableWrapper * clone() const= 0;
        virtual T* operator->() = 0;
        virtual T& operator*() = 0;
        virtual const T* operator->() const = 0;
        virtual const T& operator*() const = 0;
        virtual inline ~ClonableWrapper() {
        }
        virtual T * get_value() = 0;
        virtual const T* get_value() const = 0;
    };
    template<typename T> class TransWrapper:public ClonableWrapper<T>{
        public: 
        T value;
        template <typename...Args> TransWrapper(Args...args){
            value = T(args...);
        }
        ClonableWrapper<T>* clone()const override{
            return new TransWrapper<T>(value);
        }
        T * operator->()override{
            return &value;
        }
        T& operator*() override{
            return value;
        }
        const T * operator->()const override{
            return &value;
        }
        const T& operator*()const override{
            return value;
        }
        ~TransWrapper() override{

        }
        T * get_value()override{
            return &value;
        }
        const T* get_value() const override{
            return &value;
        }
    };
    template<typename T> class Box{
        public:
        ClonableWrapper<T> *value;
        Box(){
            value =0;
        }
        ~Box(){
            delete value;
            value =0;
        }
        template<typename U> Box(const Box<U>& other){
            T * tmp = dynamic_cast<T*>(other.value->get_value());
            if(!tmp){
                throw new std::bad_cast();
            }
            value = (ClonableWrapper<T>*)(other.value->clone());
        }
        Box(const Box<T>& other){
            value = (ClonableWrapper<T>*)(other.value->clone());
        }
        template<typename U> Box(Box<U>&& other){
            T * tmp = dynamic_cast<T*>(other.value->get_value());
            if(!tmp){
                throw new std::bad_cast();
            }
            value = (ClonableWrapper<T>*)(other.value);
            other.value = 0;
        }
        Box(const Box<T>&& other){
            value = other.value;
            other.value =0;
        }
        template<typename...Args> static Box<T> create(Args...args){
            Box out;
            out.value = new TransWrapper<T>(args...);
            return out;
        }
        T& operator*(){
            return **value;
        }
        const T& operator*()const{
            return **value;
        }
        T* operator->(){
            return (*value).operator->();
        }
        const T* operator->()const{
            return (*value).operator->();
        }
        operator T*(){
            return value->get_value();
        }
        operator const T*() const{
            return value->get_value();
        }
    };
}
