#include "middleware_router.h"

namespace lighttpning {
    
    MiddlewareChain& MiddlewareRouter::match(Request::Method method, std::string pattern) {
        auto v = new MiddlewareChain(); // TODO: delete
        return *v;
    }

    void MiddlewareRouter::call(Request& request, Response& response) const {
    }
    
}
