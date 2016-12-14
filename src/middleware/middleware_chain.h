#pragma once

#include <vector>

#include "middleware.h"
#include "middleware_function.h"

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        ~MiddlewareChain();

        MiddlewareChain& use(Middleware&);

        MiddlewareChain& use(const MiddlewareFunction::Function&);

        void call(Request&, Response&) const override;

    private:

        std::vector<Middleware*> chain;
        std::vector<Middleware*> owned;
    };

}
