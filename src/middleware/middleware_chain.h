#pragma once

#include "middleware.h"
#include "middleware_function.h"

#include <vector>

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        ~MiddlewareChain();

        MiddlewareChain& use(Middleware&);

        template<typename Function>
        MiddlewareChain& use(Function&& function) {
            auto middleware = new MiddlewareFunction<Function>(std::forward<Function>(function));
            owned.push_back(middleware);
            return use((Middleware&)*middleware); // explicit cast to use non-template overload: use(Middleware&)
        }

        void call(Request&, Response&) const override;

    private:

        std::vector<Middleware*> chain;
        std::vector<Middleware*> owned;
    };

}
