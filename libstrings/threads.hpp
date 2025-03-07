#pragma once 
#include <thread>
#include <chrono>
#include <functional>
#include <iostream>
namespace utils{
    void create_threads();
    void join_all_threads();
    void threads_should_sleep();
    void threads_shouldnt_sleep();
    void spawn_closure_internal(std::function<void(void)> func);
    void spawn_closures_internal_mult(std::vector<std::function<void(void)>> funcs);
    class ThreadFailed{
        
    };
    template<typename T> struct FutureInternal{
        volatile bool ready;
        volatile bool will_never_be_ready;
        T value;
    };
    template<typename T> class Future{
        public:
        std::shared_ptr<FutureInternal<T>> value;
        public: 
        static T get(Future<T> ptr){
            while(!ptr.value->ready){
                if(ptr.value->will_never_be_ready){
                    throw new ThreadFailed();
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
            return ptr.value->value;
        }
    };
    template<typename T> Future<T> spawn(std::function<T(void)> func ) {
        std::shared_ptr<FutureInternal<T>> outv = std::make_shared<FutureInternal<T>>();
        outv->ready = false;
        outv->will_never_be_ready = false;
        std::shared_ptr<FutureInternal<T>> inv = outv;
        auto fn = [inv, func](){
            try {
                inv->value = func();
                inv->ready = true;
            } catch(...){
                inv->will_never_be_ready = true;
            }
        };
        spawn_closure_internal(fn);
        Future<T> out;
        out.value = outv;
        return out;
    }
    template<typename T> std::vector<Future<T>> spawn_multiple(std::vector<std::function<T(void)>> funcs ) {
        std::vector<Future<T>> vout;
        std::vector<std::function<void(void)>> to_call;
        for(auto i: funcs){
            std::shared_ptr<FutureInternal<T>> outv = std::make_shared<FutureInternal<T>>();
            outv->ready = false;
            outv->will_never_be_ready = false;
            std::shared_ptr<FutureInternal<T>> inv = outv;
            auto fn = [inv, i](){
                try {
                    inv->value =i();
                    inv->ready = true;
                } catch(...){
                    inv->will_never_be_ready = true;
                }
            };
            to_call.push_back(fn);
            Future<T> out;
            out.value = outv;
            vout.push_back(out);
        }
        return vout;
    }
    template<typename T> Future<T> spawn_immediate(std::function<T(void)> func) {
        std::shared_ptr<FutureInternal<T>> outv = std::make_shared<FutureInternal<T>>();
        outv->ready = true;
        outv->will_never_be_ready = false;
        outv->value = func();
        Future<T> out;
        out.value = outv;
        return out;
    }
    template<typename T> class WorkGroup{
        std::vector<Future<T>> threads;
        public: 
        void new_job(std::function<T()> func){
            threads.push_back(spawn(func));
        }
        void new_job_immediate(std::function<T()> func){
            threads.push_back(spawn_immediate(func));
        }
        std::vector<T> join(){
            std::vector<T> out = {};
            for(int i=0; i<threads.size(); i++){
                out.push_back(Future<T>::get(threads[i]));
            }
            threads.clear();
            return out;
        }
    };
}