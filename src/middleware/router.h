#pragma once

#include <unordered_map>
#include <vector>

#include "middleware.h"
#include "middleware_chain.h"
#include "route.h"

namespace lighttpning {

    class Router : public Middleware {

    public:

        ~Router();

        template<typename Function> Router& route(
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

        std::unordered_map<Route*, MiddlewareChain*> routes;

    };
}
