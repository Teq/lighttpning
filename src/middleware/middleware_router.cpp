#include "middleware_router.h"

namespace lighttpning {

    constexpr auto regex_options = std::regex::ECMAScript;

    const std::regex MiddlewareRouter::Route::parameterNameRegex(":(\\w+)", regex_options);
    const std::string MiddlewareRouter::Route::parameterValuePattern("\\w+");

    MiddlewareRouter::Route::Route(Request::Method method, const std::string& pattern):
        routeMethod(method)
    {
        std::smatch match;
        std::string routeRegexString(pattern);

        while (std::regex_search(routeRegexString, match, parameterNameRegex)) {
            auto parameterName = match[1].str();
            parameters.push_back(parameterName);
            routeRegexString.replace(match[0].first, match[0].second, parameterValuePattern);
        }

        routeRegex.assign(routeRegexString);
    }

    bool MiddlewareRouter::Route::match(Request& request) const {

        auto result = false;

        std::smatch match;
        auto path = request.getPath();

        if (request.getMethod() == routeMethod && std::regex_match(path, match, routeRegex)) {

            uint8_t parameterIndex = 1;

            for (auto parameterName : parameters) {
                auto parameterValue = match[parameterIndex++];
                request.setParameter(parameterName, parameterValue);
            }

            result = true;
        }

        return result;
    }

    MiddlewareRouter::~MiddlewareRouter() {
        for (auto route : routes) {
            delete route.first;
            delete route.second;
        }
    }

    MiddlewareChain& MiddlewareRouter::route(Request::Method method, const std::string &pattern) {
        auto route = new Route(method, pattern);
        auto chain = new MiddlewareChain();
        this->routes.insert({ route, chain });
        return *chain;
    }

    void MiddlewareRouter::call(Request& request, Response& response) const {

        for (auto route : routes) {
            if(route.first->match(request)) {
                route.second->setNext(*next);
                route.second->call(request, response);
                return; // only the first matched route is executed
            }
        }

        if (next) {
            next->call(request, response);
        }

    }

}
