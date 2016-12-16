#pragma once

#include <vector>

#include "middleware/middleware_chain.h"
#include "middleware/middleware_router.h"

namespace lighttpning {

    class Lighttpning : private MiddlewareChain {

    public:

        ~Lighttpning();

        void handle(Connection&);

        template<typename Function> Lighttpning& router(const Function& filler) {
            auto router = new MiddlewareRouter();
            owned.push_back(router);
            filler(*router);
            return use(*router);
        };

        Lighttpning& use(Middleware&);

        // TODO: Rename it to "use" (solve overload resolution problem)
        template<typename Function> Lighttpning& useFunc(const Function& function) {
            MiddlewareChain::useFunc(function);
            return *this;
        };

    private:

        std::vector<Middleware*> owned;

    };
}
