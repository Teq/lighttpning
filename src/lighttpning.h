#pragma once

#include <vector>
#include <functional>

#include "middleware/middleware_chain.h"
#include "middleware/middleware_router.h"

namespace lighttpning {

    class Lighttpning : public MiddlewareChain {

    public:

        ~Lighttpning();

        void handle(Connection&);

        Lighttpning& router(const std::function<void(MiddlewareRouter&)>&);

        Lighttpning& use(Middleware&);

        Lighttpning& use(const MiddlewareFunction::Function&);

    private:

        std::vector<Middleware*> owned;

    };
}
