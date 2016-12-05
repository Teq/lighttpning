#include "request.h"

namespace lighttpning {

    Request::Request(ConnectionIn& in): connection(in) {}
    
    Request::Method Request::getMethod() {
        return Method::UNKNOWN;
    }
}
