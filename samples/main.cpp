#include <fstream>
#include <string>

#include "request_handler.h"
#include "http/stream_connection.h"

using namespace Lighttpning;

int main() {

    RequestHandler app;

    app.use([](Request& req, Response& res, const Middleware::Next& next) {
        auto path = req.getPath();
        std::cout << "BEGIN " + std::string(path.view(), path.size()) << std::endl;
        next();
        std::cout << "END" << std::endl;
    }).router([](Router& router) {
        router.route(Request::Method::GET, "/leds/$", [](MiddlewareChain& chain) {
            chain.use([](Request& req, Response& res, const Middleware::Next& next) {
                std::cout << "ROUTE [GET /leds/$] " << std::endl;
                next();
            });
        }).route(Request::Method::POST, "/leds/$/$", [](MiddlewareChain& chain) {
            chain.use([](Request& req, Response& res, const Middleware::Next& next) {
                std::cout << "ROUTE [POST /leds/$/$] " << std::endl;
                next();
            });
        });
    });

    std::fstream getStream("samples/get.dump");
    std::fstream postStream("samples/post.dump");
    StreamConnection getConn(getStream);
    StreamConnection postConn(postStream);
    app.handle(getConn);
    app.handle(postConn);

    return 0;
}
