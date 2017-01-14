#pragma once

#include "connection.h"

namespace Lighttpning {
    
    class Response {
        
    public:
        
        Response(const ConnectionOut&);
        
    private:
        
        const ConnectionOut& connection;
    };

}

