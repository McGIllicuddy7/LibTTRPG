#include "threads.hpp"
#include <atomic>
#include <thread>
#include <iostream>
namespace utils{
    constexpr size_t num_threads = 16;
    using std::thread;
    struct ThreadData{
        std::mutex queue_lock;
        std::vector<std::function<void(void)>> todo_queue;
        volatile bool should_join;
        volatile bool should_sleep;
        ThreadData(){
            should_join = false;
            should_sleep = false;
        }
    };
    std::vector<std::thread> threads = {};
    ThreadData thread_datas[num_threads];
    size_t next_index;
    std::mutex spawn_lock;
    void thread_run(const size_t index){
        ThreadData& self = thread_datas[index];
        while(true){
            self.queue_lock.lock();
            while(self.todo_queue.size()>0){
                std::function<void(void)> f =self.todo_queue[self.todo_queue.size()-1];
                f();
                self.todo_queue.pop_back();
            }
            self.queue_lock.unlock();
            std::this_thread::sleep_for(std::chrono::microseconds(10));
            if(self.should_join){
                return;
            }
            if(self.should_sleep){
                std::this_thread::sleep_for(std::chrono::microseconds(1000)); 
            }
        }
    }
    void spawn_closure_internal(std::function<void(void)> func){
        spawn_lock.lock();
        thread_datas[next_index].queue_lock.lock();
        thread_datas[next_index].todo_queue.push_back(func);
        thread_datas[next_index].queue_lock.unlock();
        next_index += 1;
        next_index = next_index%num_threads;
        spawn_lock.unlock();
    }
    void spawn_closures_internal_mult(std::vector<std::function<void(void)>> funcs){
        spawn_lock.lock();
        for(auto i: funcs){
            thread_datas[next_index].queue_lock.lock();
            thread_datas[next_index].todo_queue.push_back(i);
            thread_datas[next_index].queue_lock.unlock();
            next_index += 1;
            next_index = next_index%num_threads;
        }
        spawn_lock.unlock(); 
    }
    void create_threads(){
        spawn_lock.lock();
        for(size_t i=0; i<num_threads; i++){
            threads.push_back(thread((std::function<void(size_t)>)thread_run, i));
        }
        spawn_lock.unlock();
    }
    void join_all_threads(){
        spawn_lock.lock();
        for(size_t i =0; i<num_threads; i++){
            thread_datas[i].should_join = true;
        }
        for(size_t i =0; i<num_threads; i++){
            threads[i].join();
        }
        spawn_lock.unlock();
    }
    void threads_should_sleep(){
        spawn_lock.lock();
        for(size_t i =0; i<num_threads; i++){
            thread_datas[i].should_sleep = true;
        }
        spawn_lock.unlock();
    }
    void threads_shouldnt_sleep(){
        spawn_lock.lock();
        for(size_t i =0; i<num_threads; i++){
            thread_datas[i].should_sleep = false;
        }
        spawn_lock.unlock();
    }
}

