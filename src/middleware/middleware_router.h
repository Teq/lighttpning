#pragma once

#include <regex>
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
            const std::string& pattern,
            const Function& filler
        ) {
//             // TODO: figure out why it doesn't work with temp variable (probably due to lvalue/rvalue stuff..)
//             auto chain = route(method, pattern);
//             filler(chain);
            filler(route(method, pattern));
            return *this;
        };

        MiddlewareChain& route(
            Request::Method,
            const std::string& pattern
        );

        void call(Request&, Response&) const override;

    private:

        class Route {

        public:

            Route(Request::Method, const std::string& pattern);

            bool match(Request&) const;

        private:

            Request::Method routeMethod;
            std::regex routeRegex;
            std::vector<std::string> parameters;

            static const std::regex parameterNameRegex;
            static const std::string parameterValuePattern;

        };

        std::unordered_map<Route*, MiddlewareChain*> routes;

    };
}
