#pragma once

#include "../http/request.h"
#include "../http/response.h"

namespace lighttpning {

    class Middleware {

        friend class MiddlewareNode;
        friend class MiddlewareChain;
        friend class MiddlewareRouter;

    public:

        virtual ~Middleware() { }

    protected:

        Middleware();

        virtual void call(Request& request, Response& response) const = 0;

        const Middleware* next = nullptr;

        static Middleware* const FINAL;
    };

}
