#include "request.h"

namespace lighttpning {

    Request::Request(ConnectionIn& in): connection(in) {}
    
    Request::Method Request::getMethod() const {
        return method;
    }

    const std::string& Request::getPath() const {
        return path;
    }

    const std::string& Request::getParameter(const std::string& name) const {
        return parameters.at(name);
    }

    void Request::setParameter(const std::string& name, const std::string& value) {
        parameters[name] = value;

    }

}
