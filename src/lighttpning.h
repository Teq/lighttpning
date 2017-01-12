#pragma once

#include <vector>
#include <utility>

#include "middleware/middleware_chain.h"
#include "middleware/router.h"

namespace lighttpning {

    class Lighttpning : private MiddlewareChain {

    public:

        ~Lighttpning();

        void handle(Connection&);

        template<typename Function>
        Lighttpning& router(const Function& filler) {
            auto router = new Router();
            owned.push_back(router);
            filler(*router);
            return use((Middleware&)*router); // explicit cast to use non-template overload: use(Middleware&)
        }

        Lighttpning& use(Middleware&);

        template<typename Function>
        Lighttpning& use(Function&& function) {
            MiddlewareChain::use(std::forward<Function>(function));
            return *this;
        }

    private:

        std::vector<Middleware*> owned;

    };
}
