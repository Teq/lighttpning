#include "middleware_chain.h"

namespace lighttpning {

    MiddlewareChain& MiddlewareChain::use(Middleware& middleware) {

        if (chain.size() > 0) {
            chain.back()->setNext(middleware);
        }

        chain.push_back(&middleware);

        return *this;
    }

    MiddlewareChain& MiddlewareChain::use(const MiddlewareFunction::Function& middlewareFunction) {

        auto middleware = new MiddlewareFunction(middlewareFunction); // TODO: manage deletion

        return use(*middleware);
    }

    void MiddlewareChain::call(Request& request, Response& response) const {
        if (chain.size() > 0) {
            chain.back()->setNext(*next);
            chain.front()->call(request, response);
        } else if (next) {
            next->call(request, response);
        }
    }

}
