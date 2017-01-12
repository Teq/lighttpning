#pragma once

#include "middleware.h"

namespace lighttpning {

    template<typename Function>
    class MiddlewareFunction : public Middleware {

    public:

        MiddlewareFunction(Function&& function):
            func(std::forward<Function>(function))
        { }

        void call(Request& request, Response& response) const override {
            func(request, response, NextImpl(next, request, response));
        }

    private:

        class NextImpl : public Middleware::Next {

        public:

            NextImpl(const Middleware* middleware, Request& req, Response& res):
                next(middleware),
                request(req),
                response(res)
            {}

            void operator ()() const {
                if (next) {
                    next->call(request, response);
                }
            };

        private:

            const Middleware* next;
            Request& request;
            Response& response;

        };

        const Function&& func;

    };

}
