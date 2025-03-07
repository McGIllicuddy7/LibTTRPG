#pragma once 
#include "arena.hpp"
#include <string>
#include <string_view> 
#include <sstream>
#include <vector>
#include <iostream>
#include <type_traits>
#include <algorithm>
template <typename T> T random_element(const std::vector<T>& value){
    return value[rand()%value.size()];
}
template<typename T> std::vector<T> array_choose(std::vector<T> v, int num){
    std::vector<T> v1 = v;
    std::vector<T> out;
    for(int i =0 ; i<num; i++){
      int r = rand()%v1.size();
      out.push_back(v1[r]);
      v1.erase(v1.begin()+r);
    }
    return out;
}
template<typename T> bool array_contains(std::vector<T> v, T num){
    for(size_t i = 0; i<v.size(); i++){
        if(v[i] == num){
          return true;
        }
      }
      return false;
}
template<typename T> std::vector<T> array_select(std::vector<T> v, int num){
    std::vector<T> out;
    for(int i =0 ; i<num; i++){
      int r = rand()%v.size();
      out.push_back(v[r]);
    }
    return out;
}
template<typename T> std::ostream& operator<<(std::ostream& os, const std::vector<T>& obj)
{
    for(size_t i =0; i<obj.size(); i++){
        os<< obj[i];
        if (i<obj.size()-1){
            os<<",";
        }
    }
    return os;
}
namespace utils{

    enum AstNodeType{};
    class AstNode{
    }; 
    /*{"+"sv, "-"sv, "/"sv, "*"sv, "^"sv, "->"sv, "="sv, "!="sv, "-="sv, "+="sv,
    * "/="sv,"*="sv, "^="sv,"=="sv, ";"sv, "{"sv, "}"sv, "(",")"sv, "["sv, "]","&"sv, "&&"sv, "!"sv, "%"sv, "%="sv, "|"sv, "||"sv, "#"sv."<"sv, ">"sv, "<="sv, ">="sv, "<<"sv, ">>"sv, "."sv}*/
    extern const std::vector<std::string_view> default_delims;
    std::string read_file_to_string(std::string_view path);
    bool write_string_to_file(std::string_view path, std::string_view string);
    std::vector<std::string_view> split_string_by_delim(std::string_view base, std::string_view delim);
    std::vector<std::string_view> process_string_literals(std::string_view v);
    std::vector<std::string_view> split_string_by_delims(std::string_view base, std::vector<std::string_view> delims, bool extract_string_literals = true);
    std::vector<std::vector<std::string_view>> tokenize(std::string_view str,std::vector<std::string_view> delims);
     
    inline std::string format(const std::string_view fmt){
        return std::string(fmt);
    }
    template<typename T,typename... Args> std::string format(const std::string_view fmt,T value, Args...args){
        if(fmt.size() == 0){
            return "";
        } else{
            std::stringstream out;
            size_t index = (size_t)(-1);
            bool prev_was_open = false;
            for(size_t i =0; i<fmt.size()-1; i++){
                if (i<fmt.size()-3){
                    if (fmt[i] == '{' && fmt[i+1] == '{' && fmt[i+2] =='}' && fmt[i+3] =='}'){
                        out <<fmt.substr(0,i);
                        out << "{}";
                        std::string_view second = fmt.substr(i+4, fmt.size()-i-2); 
                        std::string tmp = utils::format(second,args...);
                        out <<tmp;
                        return out.str();;
                    }
                }
                if(fmt[i] == '{' && fmt[i+1] == '}'&&!prev_was_open){
                    index = i;
                    break;
                } else if (fmt[i] == '{'){
                    prev_was_open = true;
                } else{
                    prev_was_open = false;
                }
            }
            std::string_view base = fmt.substr(0,index);
            std::string_view second = fmt.substr(index+2, fmt.size()-index-2);
            out << base;
            out <<value;
            std::string tmp = utils::format(second,args...);
            out << tmp;
            return out.str();
        }
    }
    template<typename... Args>void print(const std::string_view fmt,Args...args){
        std::cout <<utils::format(fmt, args...);
    }
}
