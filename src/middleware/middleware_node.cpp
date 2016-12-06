#include "middleware.h"
#include "middleware_node.h"

namespace lighttpning {

    MiddlewareNode::MiddlewareNode(const MiddlewareFunction& middlewareFunction):
        func(middlewareFunction)
    { }

    void MiddlewareNode::call(Request& request, Response& response) const {
        NextImpl nextFunctor(*next, request, response);
        func(request, response, nextFunctor);
    }

}
