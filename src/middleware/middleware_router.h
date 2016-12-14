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

        MiddlewareRouter& route(
            Request::Method,
            const std::string& pattern,
            const std::function<void(MiddlewareChain&)>& filler
        );

        MiddlewareChain& route(Request::Method, const std::string& pattern);

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
