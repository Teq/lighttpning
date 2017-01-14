#pragma once

#include <vector>
#include <utility>

#include "middleware/middleware_chain.h"
#include "middleware/router.h"

namespace Lighttpning {

    class RequestHandler : private MiddlewareChain {

    public:

        ~RequestHandler();

        void handle(Connection&);

        template<typename Function>
        RequestHandler& router(const Function& filler) {
            auto router = new Router();
            owned.push_back(router);
            filler(*router);
            return use((Middleware&)*router); // explicit cast to use non-template overload: use(Middleware&)
        }

        RequestHandler& use(Middleware&);

        template<typename Function>
        RequestHandler& use(Function&& function) {
            MiddlewareChain::use(std::forward<Function>(function));
            return *this;
        }

    private:

        std::vector<Middleware*> owned;

    };
}
