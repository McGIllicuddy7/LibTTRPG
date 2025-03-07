#include "libstrings.hpp"
#include <fstream>
#include <iostream>
#include <unordered_set>
namespace utils{
	using std::string_view;
	using std::string;
	using std::vector;
	using std::unordered_set;
	using namespace std::literals::string_view_literals;
	const vector<string_view> default_delims = {"+"sv, "-"sv, "/"sv, "*"sv, "^"sv, "->"sv, "="sv, "!="sv, "-="sv, "+="sv,
		"/="sv,"*="sv, "^="sv,"=="sv, ";"sv, "{"sv, "}"sv, "(",")"sv, "["sv, "]","&"sv, "&&"sv, "!"sv, "%"sv, "%="sv, "|"sv, "||"sv, "#"sv,"<"sv, ">"sv, "<="sv, ">="sv, "<<"sv, ">>"sv};
	   
	   bool lookahead_matches(string_view base, size_t start, string_view delim){
		   if(start+delim.length()>base.length()){
			   return false;
		   }
		   for(size_t i=(size_t)start; i<(size_t)start+delim.length(); i++){
			   if(base[i] != delim[i-start]){
				   return false;
			   }
		   }
		   return true;
	   }
	   
	   vector<string_view> split_string_by_delim(string_view base, string_view delim){	
		   size_t start = 0;
		   vector<string_view> out;
		   for(size_t i =0; i<base.length(); i++){
			   if(lookahead_matches(base, i, delim)){
				   if(i>start){
					   out.push_back(base.substr(start,i-start));
				   }
				   while(lookahead_matches(base, i, delim)){
					   out.push_back(base.substr(i,delim.length()));
					   i += delim.length();
				   }
				   start = i;
			   }
		   }
		   if(base.length()>start){
			   out.push_back(base.substr(start,base.length()-start));
		   }
		   return out;
	   }
	   string format(const vector<string_view>& str){
		   string out = {};
		   for(size_t i =0; i<str.size(); i++){
			   out += "<";
			   out += str[i];
			   out += ">";
			   if (i<str.size()-1){
				   out += ",";
			   }
		   }
		   return out;
	   }
	   bool is_string_literal(string_view s){
		   if(s.size()<2){
			   return false;
		   }
		   if(s[0] == '"'&& s[s.length()-1] == '"'){
			   return true;
		   } else{
			   return false;
		   }
	   }
	   static size_t string_literal_end(string_view v, size_t start){
		   bool was_backslash = false;
		   for(size_t i =start; i<v.size(); i++){
			   if(v[i] == '\\' && !was_backslash){
				   was_backslash = true;
				   continue;
			   } else if(v[i] == '"' && !was_backslash){
				   return i;
			   }
			   was_backslash = false;
		   }
		   return v.length();
	   
	   }
	   vector<string_view> process_string_literals(string_view v){
		   vector<string_view> out = {};
		   size_t prev = 0;
		   for(size_t i =0; i<v.size(); i++){
			   if (v[i] == '"'){
				   out.push_back(v.substr(prev, i-prev));		
				   size_t et = string_literal_end(v, i)+1;
				   out.push_back(v.substr(i, et-i));
				   i = et;
				   prev = i;
			   }	
		   }
		   if(prev != v.size()-1){
			   out.push_back(v.substr(prev, v.size()-prev));
		   }
		   return out;
	   }
	   std::vector<std::string_view> split_string_by_delims(std::string_view base, std::vector<std::string_view> delims, bool extract_string_literals){
		   auto cmp = [](string_view a, string_view b){
			   return a.size()>b.size();
		   };
		   std::sort(delims.begin(), delims.end(), cmp);
		   unordered_set<string_view> used;
		   vector<string_view> strings;
		   if(extract_string_literals){
			   strings = process_string_literals(base);	
		   } else{
			   strings = {base};
		   }
		   for(auto i:delims){
			   vector<string_view> tmps = {};
			   for(auto j: strings){
				   if(used.count(j)){
					   tmps.push_back(j);
					   continue;
				   } 
				   if (extract_string_literals){
					   if(is_string_literal(j)){
						   tmps.push_back(j);
						   continue;
					   }
				   }
				   vector<string_view> tmp = split_string_by_delim(j, i);
				   for(auto k: tmp){
					   tmps.push_back(k);
				   }
			   }	
			   used.insert(i);
			   std::swap(tmps, strings);
			   tmps.clear();
		   }
		   return strings;
	   }
	   
	   vector<vector<string_view>> tokenize(string_view str,vector<std::string_view> delims){
		   delims.push_back(" "sv);
		   auto cmp = [](string_view a, string_view b){
			   return a.size()>b.size();
		   };
		   std::sort(delims.begin(), delims.end(), cmp);
		   vector<vector<string_view>> out = {};
		   vector<string_view> lines = split_string_by_delim(str, "\n"sv);
		   {
				vector<string_view> new_lines = {};
				for(size_t i =0; i<lines.size(); i++){
					if(i%2 == 0){
						new_lines.push_back(lines[i]);
					}
				}
				lines = std::move(new_lines);
		   }
		   for(auto i:lines){
			   vector<string_view> no_space= split_string_by_delim(i, " "sv);
			   vector<string_view> no_tab ={};
			   vector<string_view> tmp = {};
			   for(auto j: no_space){
				   vector<string_view> t = split_string_by_delim(j, "\t"sv);
				   for(auto k: t){
					   if(k != "\t"sv && k != " "sv && k != "\n"sv){
						   no_tab.push_back(k);
					   }
				   }
			   }
	   
			   for(auto j: no_tab){
				   vector<string_view> t = split_string_by_delims(j, delims);
				   for(auto k : t){
					   tmp.push_back(k);
				   }
			   }
			   out.push_back(tmp);
		   }
		   return out;
	   }
		
	   std::string read_file_to_string(std::string_view path){
		   if (std::ifstream ifs {path}) {
			   std::string data((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
			   return data;
		   }	
		   return {};
	   }
	   bool write_string_to_file(std::string_view path, std::string_view string){
		   std::fstream file {path};
		   file <<string;
		   return true;
	   }
}
