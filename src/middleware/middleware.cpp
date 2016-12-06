#include "middleware.h"

namespace lighttpning {

    Middleware::Middleware():
        next(&FINAL)
    { }

    void Middleware::setNext(const Middleware* middleware) {
        next = middleware;
    }

}
