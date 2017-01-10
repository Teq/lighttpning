#pragma once

#include "middleware.h"

#include <type_traits>
#include <functional>

namespace lighttpning {

    template<typename Function>
    class MiddlewareFunction : public Middleware {

    public:

        template<
            typename = typename std::enable_if<
                std::is_convertible<
                    Function,
                    std::function<void(Request&, Response&, const Middleware::Next&)>
                >::value &&
                std::is_rvalue_reference<Function&&>::value // Function should be passed as rvalue reference
            >::type
        >
        MiddlewareFunction(const Function&& middlewareFunction):
            func(std::move(middlewareFunction))
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
