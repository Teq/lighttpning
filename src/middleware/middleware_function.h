#pragma once

#include "middleware.h"

namespace lighttpning {

    template<typename Function>
    class MiddlewareFunction : public Middleware {

    public:

        MiddlewareFunction(const Function& middlewareFunction):
            func(middlewareFunction)
        { }

        void call(Request& request, Response& response) const override {
            func(request, response, [&]() {
                if (next) {
                    next->call(request, response);
                }
            });
        }

    private:

        const Function& func;

    };

}
