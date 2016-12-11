#include "middleware.h"

namespace lighttpning {

    void Middleware::setNext(const Middleware& middleware) {
        next = &middleware;
    }

}
