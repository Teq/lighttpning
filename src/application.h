#pragma once

#include "middleware/middleware_chain.h"

namespace lighttpning {

    class Application : public MiddlewareChain {
    public:
        void handle(Connection&);
    };
}
