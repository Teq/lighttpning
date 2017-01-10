#pragma once

#include "middleware.h"
#include "middleware_function.h"

#include <vector>
#include <type_traits>

namespace lighttpning {

    class MiddlewareChain : public Middleware {

    public:

        ~MiddlewareChain();

        MiddlewareChain& use(Middleware&);

        template<
            typename Function,
            typename = typename std::enable_if<
                !std::is_base_of<Middleware, Function>::value // This overload shouldn't hide use(Middleware&)
            >::type
        >
        MiddlewareChain& use(const Function&& function) {
            auto middleware = new MiddlewareFunction<const Function&&>(std::forward<const Function>(function));
            owned.push_back(middleware);
            return use(*middleware);
        }

        void call(Request&, Response&) const override;

    private:

        std::vector<Middleware*> chain;
        std::vector<Middleware*> owned;
    };

}
