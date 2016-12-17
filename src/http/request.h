#pragma once

#include <string>
#include <unordered_map>
#include <regex>

#include "connection.h"

namespace lighttpning {

    /**
     * Represents HTTP request
     */
    class Request {

    public:
        
        /**
         * HTTP method
         */
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
        
        /**
         * Constructor
         */
        Request(ConnectionIn&);
        
        Method getMethod();

        const std::string& getPath();

        const std::string& getParameter(uint8_t index) const;

        uint8_t addParameter(const std::string& value);

    private:

        ConnectionIn& connection;
        
        Method method = Method::UNKNOWN;
        std::string path;
        std::string httpVer;
        std::vector<std::string> parameters;
        
        static const std::regex requestLineRegex;
        static const std::regex headerLineRegex;
        static const std::unordered_map<std::string, Method> methodMap;
    };
}
