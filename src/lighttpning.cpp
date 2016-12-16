#include "lighttpning.h"

namespace lighttpning {

    Lighttpning::~Lighttpning() {
        for (auto middleware : owned) {
            delete middleware;
        }
    }

    void Lighttpning::handle(Connection& connection) {
        Request request(connection);
        Response response(connection);
        call(request, response);
    }

    Lighttpning& Lighttpning::use(Middleware& middleware) {
        MiddlewareChain::use(middleware);
        return *this;
    }

}
