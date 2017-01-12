#pragma once

#include "middleware.h"
#include "middleware_chain.h"
#include "route.h"

#include <unordered_map>

namespace lighttpning {

    class Router : public Middleware {

    public:

        ~Router();

        MiddlewareChain& route(Request::Method, StringView&& pattern);

        template<typename FillerFunction> Router& route(
            Request::Method method,
            StringView&& pattern,
            const FillerFunction& filler
        ) {
            filler(route(method, std::move(pattern)));
            return *this;
        }

        void call(Request&, Response&) const override;

    private:

        std::unordered_map<Route*, MiddlewareChain*> routes;

    };
}
