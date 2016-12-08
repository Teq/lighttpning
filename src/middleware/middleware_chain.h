#pragma once

#include <vector>

#include "middleware.h"

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        MiddlewareChain();

        MiddlewareChain& use(Middleware&);

        MiddlewareChain& use(const Middleware::Function&);

    protected:

        std::vector<Middleware*> chain;
    };

}
