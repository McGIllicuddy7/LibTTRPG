#include <stdio.h>
#include "arena.hpp"
#include <cstring>
#include <string_view>
#include <print>
#include "libstrings.hpp"
#include "threads.hpp"
using std::vector;
using std::string;
using std::string_view;
using namespace std::literals::string_view_literals;
using utils::spawn;
using utils::Future;
using std::println;
//with futures./a.out  5.48s user 0.09s system 426% cpu 1.308 total
//without futures ./a.out  5.59s user 0.10s system 451% cpu 1.262 total
//without futures ./a.out  17.57s user 0.22s system 98% cpu 18.138 total
//with future ./a.out  22.09s user 0.25s system 500% cpu 4.460 total
//with future ./a.out  0.55s user 0.01s system 200% cpu 0.281 total
//without future ./a.out  0.42s user 0.01s system 74% cpu 0.573 total

//with futures ./a.out  2.94s user 0.04s system 538% cpu 0.553 total
//without futures ./a.out  8.22s user 0.06s system 737% cpu 1.121 total

//with locks Time taken by function: 9336 milliseconds
size_t add_up(size_t up_to){
	size_t out =0;
	for(size_t i =1; i<up_to*1000; i++){
		out += i;
	}
	return out;
}
void add_test(){
	constexpr size_t count = 1'000;
	bool use_futures = true;
	utils::create_threads();
	if(use_futures){
		vector<Future<size_t>> ints;
		for(size_t i =0; i<count; i++){
			ints.push_back(spawn((std::function<size_t(void)>)[i](){return add_up(i);}));
		}
		for(auto i: ints){
			std::cout <<Future<size_t>::get(i)<< "\n";
		}
	} else{
		for(size_t i =0; i<count; i++){
			std::cout <<add_up(i)<<"\n";
		}
	}
	utils::join_all_threads();
}
int main(){
	RefSlice<int> ints = RefSlice<int>::make(100);	
	for(size_t i =0; i<ints.size(); i++){
		ints[i] =i;
	}
	for(auto & i: ints){
		std::println("{}",i);
	}
	WeakSlice<int> wints= ints;
	for(auto &i :wints){
		println("{}", i);
	}
}
