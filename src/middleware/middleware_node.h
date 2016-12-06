#pragma once

#include "../http/request.h"
#include "../http/response.h"
#include "middleware.h"

namespace lighttpning {

    using MiddlewareFunction = void (*)(Request& req, Response& res, const Next& next);

    class MiddlewareNode : public Middleware {

    public:

        MiddlewareNode(const MiddlewareFunction&);

    protected:

        void call(Request&, Response&) const override;

        const MiddlewareFunction& func;

        class NextImpl : public Next {
        public:
            NextImpl (const Middleware& middleware, Request& request, Response& response) :
                middleware(middleware),
                request(request),
                response(response)
            { }

            void operator() () const override {
                middleware.call(request, response);
            }

        private:
            const Middleware& middleware;
            Request& request;
            Response& response;
        };

    };

}
