#include "middleware_chain.h"

namespace lighttpning {

    MiddlewareChain::MiddlewareChain(): Middleware([&](Request& request, Response& response, const Next& next) {
        if (chain.size() > 0) {
            chain.front()->call(request, response);
        }
    }) {}

    MiddlewareChain& MiddlewareChain::use(Middleware& middleware) {

        if (chain.size() > 0) {
            auto last = chain.back();
            last->next = &middleware;
        }

        middleware.next = next;
        chain.push_back(&middleware);

        return *this;
    }

    MiddlewareChain& MiddlewareChain::use(const Middleware::Function& middlewareFunction) {

        auto middleware = new Middleware(middlewareFunction);
        use(*middleware);

        return *this;
    }

}
