#pragma once

#include <regex>

#include "middleware.h"
#include "middleware_chain.h"

namespace lighttpning {

    class MiddlewareRouter : public Middleware {

    public:

        MiddlewareChain& match(Request::Method method, std::string pattern);

        void call(Request&, Response&) const override;

    private:

        static const std::regex paramRegex;

    };
}
