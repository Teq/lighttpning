#pragma once

#include "../http/request.h"
#include "../http/response.h"
#include "middleware.h"

namespace lighttpning {

    using MiddlewareFunction = void (*)(Request& req, Response& res, const Next& next);

    class MiddlewareNode : public Middleware {
    public:

        MiddlewareNode(const MiddlewareFunction&);

        void call(Request& request, Response& response) const override;
        void setNext(const Middleware& middleware) override;

    private:
        const Middleware* next = nullptr;
        const MiddlewareFunction& func;
    };


}
