#pragma once

#include <string>

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

}
