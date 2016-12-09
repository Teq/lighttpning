#include "request.h"

namespace lighttpning {

    Request::Request(ConnectionIn& in): connection(in) {}
    
    Request::Method Request::getMethod() {
        return Method::UNKNOWN;
    }
    
    const std::string& Request::getParameter(const std::string& name) const {
        return parameters.at(name);
    }
    
}
