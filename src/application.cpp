#include "application.h"

namespace lighttpning {

    void Application::handle(Connection& connection) {
        Request request(connection);
        Response response(connection);
        call(request, response);
    }

    void Application::use(const MiddlewareFunction& middlewareFunction) {
        auto middleware = new MiddlewareNode(middlewareFunction);
        use(*middleware);
    }

}
