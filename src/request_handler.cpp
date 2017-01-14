#include "request_handler.h"

namespace Lighttpning {

    RequestHandler::~RequestHandler() {
        for (auto middleware : owned) {
            delete middleware;
        }
    }

    void RequestHandler::handle(Connection& connection) {
        Request request(connection);
        Response response(connection);
        call(request, response);
    }

    RequestHandler& RequestHandler::use(Middleware& middleware) {
        MiddlewareChain::use(middleware);
        return *this;
    }

}
