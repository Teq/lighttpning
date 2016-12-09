#include "middleware_function.h"

namespace lighttpning {

    MiddlewareFunction::MiddlewareFunction(const Function& middlewareFunction):
        func(middlewareFunction)
    { }

    void MiddlewareFunction::call(Request& request, Response& response) const {
        func(request, response, [&]() {
            if (next) {
                next->call(request, response);
            }
        });
    }

}
