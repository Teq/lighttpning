#pragma once

#include "middleware.h"
#include "middleware_chain.h"

namespace lighttpning {

    class MiddlewareRouter : public Middleware {

    public:

        MiddlewareChain& match(Request::Method method, std::string pattern);

    protected:
        
        void call(Request&, Response&) const override;

    };
}
