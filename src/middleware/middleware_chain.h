#pragma once

#include <vector>

#include "middleware.h"
#include "middleware_function.h"

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        ~MiddlewareChain();

        MiddlewareChain& use(Middleware&);

        template<typename Function> MiddlewareChain& func(const Function& function) {
            auto middleware = new MiddlewareFunction<Function>(function);
            owned.push_back(middleware);

            return use(*middleware);
        };

        void call(Request&, Response&) const override;

    private:

        std::vector<Middleware*> chain;
        std::vector<Middleware*> owned;
    };

}
