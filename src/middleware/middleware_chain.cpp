#include "middleware_chain.h"

namespace lighttpning {

    MiddlewareChain::MiddlewareChain():
        next(&FINAL)
    {}

    void MiddlewareChain::use(Middleware& middleware) {

        if (chain.size() > 0) {
            auto prev = chain.back();
            prev->setNext(middleware);
            middleware.setNext(*next);
        }

        chain.push_back(&middleware);
    }

    void MiddlewareChain::use(const MiddlewareFunction& middlewareFunction) {
        auto middleware = new MiddlewareNode(middlewareFunction);
        use(*middleware);
    }

    void MiddlewareChain::call(Request& request, Response& response) const {
        if (chain.size() > 0) {
            auto first = chain.front();
            first->call(request, response);
        }
    }

    void MiddlewareChain::setNext(const Middleware& middleware) {
        next = &middleware;
    }

}
