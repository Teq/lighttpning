#include "request.h"

namespace lighttpning {

    constexpr auto regex_options = std::regex::ECMAScript;

    const std::regex Request::requestLineRegex("([A-Z]+) +(\\S+) +HTTP/(.+)\r\n", regex_options);

    const std::regex Request::headerLineRegex("", regex_options);

    const std::unordered_map<std::string, Request::Method> Request::methodMap = {
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
    
    Request::Request(ConnectionIn& in):
        connection(in)
    {}
    
    Request::Method Request::getMethod() {
        
        if (method == Method::UNKNOWN) {
            
            char buffer[256];
            size_t size = connection.read('\n', buffer, 256);
            std::string line(buffer, size);

            std::smatch match;
            
            if (std::regex_match(line, match, requestLineRegex) && match.size() == 4) {

                method = methodMap.at(match[1].str());
                path = match[2].str();
                httpVer = match[3].str();

            } else {
//                 throw std::invalid_argument("Invalid request line");
            }
        }
        
        return method;
    }

    const std::string& Request::getPath() {
        return path;
    }

    const std::string& Request::getParameter(uint8_t index) const {
        return parameters.at(index);
    }

    uint8_t Request::addParameter(const std::string& value) {
        parameters.push_back(value);
    }

}
