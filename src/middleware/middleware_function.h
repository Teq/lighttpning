#pragma once

#include "middleware.h"

namespace lighttpning {

    template<typename Function>
    class MiddlewareFunction : public Middleware {

    public:

        MiddlewareFunction(const Function& middlewareFunction):
            func(middlewareFunction)
        { }

        void call(Request& request, Response& response) const override {
            func(request, response, NextImpl(next, request, response));
        }

    private:

        class NextImpl : public Middleware::Next {

        public:

            NextImpl(const Middleware* mw, Request& req, Response& res):
                middleware(mw),
                request(req),
                response(res)
            {}

            void operator ()() const {
                if (middleware) {
                    middleware->call(request, response);
                }
            };

        private:

            const Middleware* middleware;
            Request& request;
            Response& response;

        };

        const Function& func;

    };

}
