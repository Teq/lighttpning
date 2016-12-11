#include "middleware_router.h"

namespace lighttpning {

    constexpr auto regex_options = std::regex::ECMAScript;

    const std::regex MiddlewareRouter::paramRegex("", regex_options);

    MiddlewareChain& MiddlewareRouter::match(Request::Method method, std::string pattern) {
        auto v = new MiddlewareChain(); // TODO: delete
        return *v;
    }

    void MiddlewareRouter::call(Request& request, Response& response) const {
    }
    
}
