#include "router.h"

namespace lighttpning {

    Router::~Router() {
        for (auto route : routes) {
            delete route.first;
            delete route.second;
        }
    }

    MiddlewareChain& Router::route(
        Request::Method method,
        StringView pattern
    ) {
        auto route = new Route(method, pattern);
        auto chain = new MiddlewareChain();
        routes.insert({ route, chain });
        return *chain;
    }

    void Router::call(Request& request, Response& response) const {

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
