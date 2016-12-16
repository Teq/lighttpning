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

//     Lighttpning& Lighttpning::router(const std::function<void(MiddlewareRouter&)>& filler) {
//         auto router = new MiddlewareRouter();
//         owned.push_back(router);
//         filler(*router);
//         return use(*router);
//     }

    Lighttpning& Lighttpning::use(Middleware& middleware) {
        MiddlewareChain::use(middleware);
        return *this;
    }

    Lighttpning& Lighttpning::use(const MiddlewareFunction::Function& function) {
        MiddlewareChain::use(function);
        return *this;
    }

}
