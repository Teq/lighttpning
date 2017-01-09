#pragma once

#include <vector>

#include "middleware.h"
#include "middleware_function.h"

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        ~MiddlewareChain();

        MiddlewareChain& use(Middleware&);

        // Make sure it can only accept rvalue references
        template<typename Function, class = typename std::enable_if<std::is_rvalue_reference<Function&&>::value>::type>
        MiddlewareChain& use(Function&& function) {
            auto middleware = new MiddlewareFunction<Function>(function); // TODO: try std::move
            owned.push_back(middleware);
            return use(*middleware);
        }

        void call(Request&, Response&) const override;

    private:

        std::vector<Middleware*> chain;
        std::vector<Middleware*> owned;
    };

}
