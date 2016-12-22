#pragma once

#include "connection.h"

namespace lighttpning {
    
    class Response {
        
    public:
        
        Response(const ConnectionOut&);
        
    private:
        
        const ConnectionOut& connection;
    };

}

