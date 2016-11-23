#pragma once

#include <vector>

#include "middleware.h"

using std::vector;

namespace Lighttpning {

    class Application {

    public:
        void use(Middleware& middleware) {

            if (middlewares.size() > 0) {
                auto prev = middlewares.back();
                prev->setNext(middleware);
            }

            middlewares.push_back(&middleware);
        }

        void use(const MiddlewareFunc& func) {
            auto middleware = new MiddlewareImpl(func);
            return use(*middleware);
        }

        void request(HttpContext& context) {
            if (middlewares.size() > 0) {
                auto first = middlewares.front();
                first->call(context);
            }
        }

    private:
        vector<Middleware *> middlewares;
    };
}
