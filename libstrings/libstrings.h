#pragma once 
#include "arena.h"
#include <string>
#include <string_view>
#include <vector>
/*{"+"sv, "-"sv, "/"sv, "*"sv, "^"sv, "->"sv, "="sv, "!="sv, "-="sv, "+="sv,
 * "/="sv,"*="sv, "^="sv,"=="sv, ";"sv, "{"sv, "}"sv, "(",")"sv, "["sv, "]","&"sv, "&&"sv, "!"sv, "%"sv, "%="sv, "|"sv, "||"sv, "#"sv."<"sv, ">"sv, "<="sv, ">="sv, "<<"sv, ">>"sv}*/
extern const std::vector<std::string_view> default_delims;
std::string read_file_to_string(std::string_view path);
bool write_string_to_file(std::string_view path, std::string_view string);
std::vector<std::string_view> split_string_by_delim(std::string_view base, std::string_view delim);
std::vector<std::string_view> process_string_literals(std::string_view v);
std::vector<std::string_view> split_string_by_delims(std::string_view base, std::vector<std::string_view> delims, bool extract_string_literals = true);
std::string format(const std::vector<std::string_view>& str);
std::vector<std::vector<std::string_view>> tokenize(std::string_view str,std::vector<std::string_view> delims);
