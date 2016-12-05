#include "application.h"
#include "http/response.h"
#include "http/request.h"

namespace lighttpning {

    void Application::use(Middleware& middleware) {

        if (middlewares.size() > 0) {
            auto prev = middlewares.back();
            prev->setNext(middleware);
        }

        middlewares.push_back(&middleware);
    }

    void Application::use(const MiddlewareFunction& middlewareFunction) {
        auto middleware = new MiddlewareImpl(middlewareFunction);
        use(*middleware);
    }

    void Application::handle(Connection& connection) {
        Request req(connection);
        Response res(connection);
        if (middlewares.size() > 0) {
            auto first = middlewares.front();
            first->call(req, res);
        }
    }
    
}
