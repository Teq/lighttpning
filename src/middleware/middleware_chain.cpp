#include "middleware_chain.h"

namespace lighttpning {

    void MiddlewareChain::use(Middleware& middleware) {

        if (chain.size() > 0) {
            auto prev = chain.back();
            prev->setNext(&middleware);
        }

        middleware.setNext(next);
        chain.push_back(&middleware);
    }

    void MiddlewareChain::call(Request& request, Response& response) const {
        if (chain.size() > 0) {
            chain.front()->call(request, response);
        }
    }

}
