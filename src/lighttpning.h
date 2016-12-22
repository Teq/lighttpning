#pragma once

#include <vector>

#include "middleware/middleware_chain.h"
#include "middleware/router.h"

namespace lighttpning {

    class Lighttpning : private MiddlewareChain {

    public:

        ~Lighttpning();

        void handle(Connection&);

        template<typename Function> Lighttpning& router(const Function& filler) {
            auto router = new Router();
            owned.push_back(router);
            filler(*router);
            return use(*router);
        };

        Lighttpning& use(Middleware&);

        template<typename Function> Lighttpning& func(const Function& function) {
            MiddlewareChain::func(function);
            return *this;
        };

    private:

        std::vector<Middleware*> owned;

    };
}
