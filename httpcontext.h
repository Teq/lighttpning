#pragma once

#include <string>
#include <regex>
#include <unordered_map>
#include <exception>

namespace Lighttpning {

    struct Request {
        enum class Method : unsigned char {
            UNKNOWN,
            OPTIONS,
            GET,
            HEAD,
            POST,
            PUT,
            PATCH,
            DELETE,
            TRACE,
            CONNECT
        };
        Method method = Method::UNKNOWN;
        std::string path;
        std::string httpVer;
        std::string query;
    };

    struct Response {
        unsigned char status;
    };

    struct HttpContext {
        Request request;
        Response response;
    };

//    class StringBuffer {
//
//    public:
//
//        StringBuffer() {
//            buf = (char*)malloc(buf_len);
//        }
//
//        ~StringBuffer() {
//            free(buf);
//        }
//
//        void operator += (char c) {
//            buf[buf_cur++] = c;
//            if (buf_cur >= buf_len) {
//                buf_len *= 1.5;
//                void* newPtr = realloc(buf, buf_len);
//                if (newPtr == nullptr) {
//                    throw new std::runtime_error("Unable to allocate memory");
//                } else {
//                    buf = (char*)newPtr;
//                }
//            }
//        }
//
//        inline bool empty() {
//            return buf_cur == 0;
//        }
//
//        void clear() {
//            buf_len = DEFAULT_BUF_LEN;
//            buf = (char*)realloc(buf, buf_len); // realloc to lower size, should not fail
//            buf_cur = 0;
//        }
//
//    private:
//
//        constexpr unsigned short DEFAULT_BUF_LEN = 8;
//        char* buf = nullptr;
//        unsigned short buf_cur = 0;
//        unsigned short buf_len = DEFAULT_BUF_LEN;
//
//    };

    class RequestParser {
    public:

        HttpContext* putchar(const char c) {

            HttpContext* result = nullptr;

            // init context if it's not here
            if (!ctx) {
                ctx = new HttpContext();
            }

            if (c == '\n') {

                if (line.empty()) { // 2 new lines in a row => headers parsed
                    // TODO: decide on message body
                    result = ctx;
                    ctx = nullptr;
                } else { // header line
                    parseLine(*ctx, line);
                    line.clear();
                }

            } else if (c != '\r') { // just skip CR (RFC allows)
                line += c;
            }

            return result;
        }

    private:

        static const std::regex request_line_regex;
        static const std::regex header_line_regex;
        static const std::unordered_map<std::string, Request::Method> method_map;

        static void parseLine(HttpContext& ctx, const std::string& line) {
            if (ctx.request.method == Request::Method::UNKNOWN) {
                // expect request line
                std::smatch match;
                if (std::regex_match(line, match, request_line_regex) && match.size() == 4) {
                    ctx.request.method = method_map.at(match[1].str());
                    ctx.request.path = match[2].str();
                    ctx.request.httpVer = match[3].str();

                } else {
                    throw new std::invalid_argument("Invalid request line");
                }

            } else {
                // header line

            }
        }

        HttpContext* ctx = nullptr;
        std::string line;
    };

    constexpr auto regex_options = std::regex::ECMAScript;
    const std::regex RequestParser::request_line_regex("^(GET|POST) +(\\S+) +HTTP/(.+)$", regex_options);
    const std::regex RequestParser::header_line_regex("", regex_options);

    const std::unordered_map<std::string, Request::Method> RequestParser::method_map = {
            { "OPTIONS", Request::Method::OPTIONS },
            { "GET",     Request::Method::GET     },
            { "HEAD",    Request::Method::HEAD    },
            { "POST",    Request::Method::POST    },
            { "PUT",     Request::Method::PUT     },
            { "PATCH",   Request::Method::PATCH   },
            { "DELETE",  Request::Method::DELETE  },
            { "TRACE",   Request::Method::TRACE   },
            { "CONNECT", Request::Method::CONNECT }
    };

}
