#include "middleware.h"

namespace lighttpning {

    Middleware::Middleware(const Function& middlewareFunction):
        func(middlewareFunction)
    { }

    void Middleware::call(Request& request, Response& response) const {
        func(request, response, [&]() {
            if (next) {
                next->call(request, response);
            }
        });
    }

}
