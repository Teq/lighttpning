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
        
        Method getMethod() const;

        const std::string& getPath() const;

        const std::string& getParameter(const std::string& name) const;

        void setParameter(const std::string& name, const std::string& value);

    private:

        Method method = Method::UNKNOWN;
        std::string path;
        std::unordered_map<std::string, std::string> parameters;
        ConnectionIn& connection;
    };
}
