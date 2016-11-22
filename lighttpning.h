#pragma once

#include <vector>

#include "middleware.h"

using std::vector;

namespace Lighttpning {

    class Application {

    public:
        void use(const MiddlewareFunc& func) {

            Middleware* prev = nullptr;

            if (middlewares.size() > 0) {
                prev = middlewares.back();
            }

            auto next = new MiddlewareImpl(func);
            next->setNext(final);

            if (prev) {
                prev->setNext(*next);
            }

            middlewares.push_back(next);
        }

        void request() {
            if (middlewares.size() > 0) {
                auto first = middlewares.front();
                first->call();
            }
        }

    private:
        vector<Middleware *> middlewares;
        MiddlewareFinal final;
    };
}
