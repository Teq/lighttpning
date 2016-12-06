#pragma once

#include <vector>

#include "middleware_node.h"
#include "middleware_node.h"

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        void use(Middleware&);

    protected:

        void call(Request&, Response&) const override;

        std::vector<Middleware*> chain;
    };

}
