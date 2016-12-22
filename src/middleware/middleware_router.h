#pragma once

#include <unordered_map>
#include <vector>

#include "middleware.h"
#include "middleware_chain.h"

namespace lighttpning {

    class MiddlewareRouter : public Middleware {

    public:

        ~MiddlewareRouter();

        template<typename Function> MiddlewareRouter& route(
            Request::Method method,
            StringView pattern,
            const Function& filler
        ) {
            filler(route(method, pattern));
            return *this;
        };

        MiddlewareChain& route(Request::Method, StringView pattern);

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
