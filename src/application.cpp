#include "application.h"

namespace lighttpning {

    void Application::handle(Connection& connection) {
        Request request(connection);
        Response response(connection);
        call(request, response);
    }

}
