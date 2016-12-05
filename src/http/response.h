#pragma once

#include <string>
#include <unordered_map>

#include "connection.h"

namespace lighttpning {
    class Response {
    public:
        Response(const ConnectionOut& out): connection(out) {}
        void getMethod();
        unsigned char status;
    private:
        const ConnectionOut& connection;
    };

}

