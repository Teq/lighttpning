#include "middleware.h"
#include "middleware_node.h"

namespace lighttpning {

    MiddlewareNode::MiddlewareNode(const Function& middlewareFunction):
        func(middlewareFunction)
    { }

    void MiddlewareNode::call(Request& request, Response& response) const {
        NextMiddlewareWrapper wrapper(*next, request, response);
        func(request, response, wrapper);
    }

}
