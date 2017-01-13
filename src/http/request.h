#pragma once

#include "connection.h"
#include "misc/string_buffer.h"
#include "misc/string_view.h"

#include <vector>

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

        const StringView getPath();

        const StringView& getParameter(size_t index) const;

        size_t addParameter(StringView&& value);

        size_t addParameter(const char* ptr, size_t size);

    private:

        static constexpr size_t DEFAULT_STR_BUFF_SIZE = 64;
        static constexpr size_t MAX_HTTP_METHOD_STR_SIZE = 8;
        static constexpr size_t MAX_HTTP_PATH_STR_SIZE = 256;
        static constexpr size_t MAX_HTTP_VERSION_STR_SIZE = 10;

        ConnectionIn& connection;
        
        Method method = Method::UNKNOWN;
        StringBuffer requestLineBuffer;
        StringBuffer headerLineBuffer;
        std::vector<StringView> pathParams;
    };
}
