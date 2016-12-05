#pragma once

#include <string>
#include <unordered_map>

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
        
        /**
         * Get HTTP method
         */
        Method getMethod();
        
        /**
         * Get complete request URL (incl. host, path and query string)
         * E.g.: "example.com/info/about.html?lang=en"
         */
        std::string getUrl();
        
        
        /**
         * Get path from request URL
         * E.g.: "/info/about.html" in "example.com/info/about.html?lang=en"
         */
        std::string getPath();
        
        /**
         * Get query string parameters
         */
        std::unordered_map<std::string, std::string> getQuery();
        
        /**
         * Get request headers
         */
        std::unordered_map<std::string, std::string> getHeaders();
        
    private:
        Method method = Method::UNKNOWN;
        std::string path;
        std::string query;
        std::string httpVer;
        std::unordered_map<std::string, std::string> headers;
        ConnectionIn& connection;
    };
}
