// #pragma once
// 
// #include <string>
// #include <regex>
// #include <unordered_map>
// 
// #include "http_context.h"
// 
// namespace lighttpning {
// 
//     class PutcharAdapter {
//     public:
// 
//         HttpContext* putchar(const char);
// 
//     private:
// 
//         static const std::regex request_line_regex;
//         static const std::regex header_line_regex;
//         static const std::unordered_map<std::string, Request::Method> method_map;
// 
//         static void parseLine(HttpContext&, const std::string&);
// 
//         HttpContext* ctx = nullptr;
//         std::string line;
//     };
// 
// }
