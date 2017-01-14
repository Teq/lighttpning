#include "middleware.h"

namespace Lighttpning {

    void Middleware::setNext(const Middleware& middleware) {
        next = &middleware;
    }

}
