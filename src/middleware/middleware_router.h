#pragma once

#include <unordered_map>
#include <vector>

#include "middleware.h"
#include "middleware_chain.h"

namespace lighttpning {

    class MiddlewareRouter : public Middleware {

    public:

        ~MiddlewareRouter();

        template<typename Function, typename Pattern> MiddlewareRouter& route(
            Request::Method method,
            Pattern pattern,
            const Function& filler
        ) {
//             // TODO: figure out why it doesn't work with temp variable (probably due to lvalue/rvalue stuff..)
//             auto chain = route(method, pattern);
//             filler(chain);
            filler(route(method, pattern));
            return *this;
        };

        MiddlewareChain& route(Request::Method, StringView pattern);

        MiddlewareChain& route(Request::Method, const char* pattern);

        void call(Request&, Response&) const override;

    private:

        class Route {

        public:

            Route(Request::Method, StringView pattern);

            bool match(Request&) const;

        private:

            Request::Method method;
            StringView pattern;

        };

        std::unordered_map<Route*, MiddlewareChain*> routes;

    };
}
