#include <stdio.h>
#include "arena.hpp"
#include <cstring>
#include <string_view>
#include <iostream>
#include "libstrings.hpp"
using std::vector;
using std::string;
using std::string_view;
using namespace std::literals::string_view_literals;
int main(){
	string file =utils::read_file_to_string("main.cpp");
	vector<vector<string_view>> strings = utils::tokenize(file,utils::default_delims);
	for(auto &k : strings){
		std::cout << k<<"\n";
	}
}
