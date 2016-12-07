#pragma once

#include "middleware/middleware_chain.h"

namespace lighttpning {

    class Application : public MiddlewareChain {
    public:
        using MiddlewareChain::use;
        void use(const MiddlewareNode::Function&);
        void handle(Connection&);
    };
}
