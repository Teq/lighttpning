#pragma once

#include "../http/request.h"
#include "../http/response.h"

namespace lighttpning {

    class Middleware {
        
    public:

        virtual ~Middleware() { };

        virtual void call(Request&, Response&) const = 0;

        void setNext(const Middleware&);

    protected:

        const Middleware* next = nullptr;

    };

}
