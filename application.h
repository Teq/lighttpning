#pragma once

#include <vector>

#include "middleware.h"

using std::vector;

namespace Lighttpning {

    class Application {

    public:

        /**
         * Add given middleware to pipeline
         * @param middleware Middleware
         */
        void use(Middleware& middleware) {

            if (middlewares.size() > 0) {
                auto prev = middlewares.back();
                prev->setNext(middleware);
            }

            middlewares.push_back(&middleware);
        }

        /**
         * Add given middleware function to pipeline
         * @param middlewareFunction Middleware function
         */
        void use(const MiddlewareFunction& middlewareFunction) {
            auto middleware = new MiddlewareImpl(middlewareFunction);
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
