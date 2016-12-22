#include "router.h"

namespace lighttpning {


    Router::Route::Route(Request::Method method, StringView pattern):
        method(method),
        pattern(pattern)
    { }

    bool Router::Route::match(Request& request) const {

        bool match = true;

        if (request.getMethod() == method) {

            auto path = request.getPath();

            const char* patternPtr = pattern.view();
            const char* pathPtr = path.view();

            while (pattern.includes(patternPtr) && path.includes(pathPtr)) {
                
                char patternChar = *patternPtr;
                char pathChar = *pathPtr;
                                
                if (patternChar == '$') { // parameter placeholder encountered
                    
                    size_t len = 0;
                    
                    while (path.includes(pathPtr + len)) {

                        pathChar = pathPtr[len];
                        
                        if (
                            (pathChar >= '0' && pathChar <= '9') ||
                            (pathChar >= 'a' && pathChar <= 'z') ||
                            (pathChar >= 'A' && pathChar <= 'Z') ||
                            (pathChar == '_') // TODO: try isalpha(c), isdigit(c)
                        ) {
                            len++;
                        } else {
                            break;
                        }
                                                
                    }
                    
                    if (len > 0) {
                        request.addParameter(pathPtr, len);
                    }
                    
                    patternPtr++;
                    pathPtr += len;
                    
                } else if (patternChar != pathChar) {
                    
                    match = false;
                    break;
                    
                } else {

                    patternPtr++;
                    pathPtr++;
                    
                }
                
            }

            if (pattern.includes(patternPtr) || path.includes(pathPtr)) {
                match = false;
            }
            
        } else {
            match = false;
        }

        return match;
    }

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
