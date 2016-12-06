#include "middleware.h"
#include "middleware_node.h"

namespace lighttpning {

    class NextImpl : public Next {
    public:
        NextImpl (const Middleware& middleware, Request& request, Response& response) :
            middleware(middleware),
            request(request),
            response(response)
        { }

        void operator() () const override {
            middleware.call(request, response);
        }

    private:
        const Middleware& middleware;
        Request& request;
        Response& response;
    };

    MiddlewareNode::MiddlewareNode(const MiddlewareFunction& middlewareFunction):
        func(middlewareFunction),
        next(&FINAL)
    { }

    void MiddlewareNode::call(Request& request, Response& response) const {
        NextImpl nextFunctor(*next, request, response);
        func(request, response, nextFunctor);
    }

    void MiddlewareNode::setNext(const Middleware& middleware) {
        next = &middleware;
    }

}
