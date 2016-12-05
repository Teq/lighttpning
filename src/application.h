#pragma once

#include <vector>

#include "middleware.h"

namespace lighttpning {

    class Application {
    public:
        void use(Middleware&);
        void use(const MiddlewareFunction&);
        void handle(Connection&);

    private:
        std::vector<Middleware*> middlewares;
    };
}
