#pragma once

#include <vector>
#include <type_traits>

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
            return use(*router);
        }

        Lighttpning& use(Middleware&);

        // Make sure it can only accept rvalue references
        template<typename Function, class = typename std::enable_if<std::is_rvalue_reference<Function&&>::value>::type>
        Lighttpning& use(Function&& function) {
            MiddlewareChain::use(std::move(function));
            return *this;
        }

    private:

        std::vector<Middleware*> owned;

    };
}
