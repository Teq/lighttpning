#pragma once

#include <string>

#include "connection.h"

namespace lighttpning {
    
    class Response {
        
    public:
        
        Response(const ConnectionOut&);
        
    private:
        
        const ConnectionOut& connection;
    };

}

