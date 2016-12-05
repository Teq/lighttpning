// #include <exception>
// 
// #include "putchar_adapter.h"
// 
// namespace lighttpning {
// 
//     // initializers
// 
//     constexpr auto regex_options = std::regex::ECMAScript;
// 
//     const std::regex PutcharAdapter::request_line_regex("^([A-Z]+) +(\\S+) +HTTP/(.+)$", regex_options);
// 
//     const std::regex PutcharAdapter::header_line_regex("", regex_options);
// 
//     const std::unordered_map<std::string, Request::Method> PutcharAdapter::method_map = {
//             { "OPTIONS", Request::Method::OPTIONS },
//             { "GET",     Request::Method::GET     },
//             { "HEAD",    Request::Method::HEAD    },
//             { "POST",    Request::Method::POST    },
//             { "PUT",     Request::Method::PUT     },
//             { "PATCH",   Request::Method::PATCH   },
//             { "DELETE",  Request::Method::DELETE  },
//             { "TRACE",   Request::Method::TRACE   },
//             { "CONNECT", Request::Method::CONNECT }
//     };
// 
//     // constructor
// 
//     HttpContext* PutcharAdapter::putchar(const char c) {
// 
//         HttpContext* result = nullptr;
// 
//         // init context if it's not here
//         if (!ctx) {
//             ctx = new HttpContext();
//         }
// 
//         if (c == '\n') {
// 
//             if (line.empty()) { // 2 new lines in a row => headers parsed
//                 // TODO: decide on message body
//                 result = ctx;
//                 ctx = nullptr;
//             } else { // header line
//                 parseLine(*ctx, line);
//                 line.clear();
//             }
// 
//         } else if (c != '\r') { // just skip CR (RFC allows that)
//             line += c;
//         }
// 
//         return result;
//     }
// 
//     // members
// 
//     void PutcharAdapter::parseLine(HttpContext& ctx, const std::string& line) {
// 
//         std::smatch match;
// 
//         if (ctx.request.method == Request::Method::UNKNOWN) {
// 
//             // request line
// 
//             if (std::regex_match(line, match, request_line_regex) && match.size() == 4) {
// 
//                 ctx.request.method = method_map.at(match[1].str());
//                 ctx.request.path = match[2].str();
//                 ctx.request.httpVer = match[3].str();
// 
//             } else {
//                 throw new std::invalid_argument("Invalid request line");
//             }
// 
//         } else {
// 
//             // header line
// 
//             if (std::regex_match(line, match, header_line_regex) && match.size() == 3) {
// 
//                 auto name = match[1].str();
//                 auto value = match[2].str();
//                 ctx.request.headers.insert({ name, value });
// 
//             } else {
// 
//                 // multi-line header
// 
//             }
//         }
// 
//     }
// 
// }
