#include <fstream>

#include "../src/lighttpning.h"
#include "../src/http/stream_connection.h"

using namespace lighttpning;

int main() {

    Lighttpning app;

    app.useFunc([](Request& req, Response& res, const auto& next) {
        std::cout << "BEGIN" << std::endl;
        next();
        std::cout << "END" << std::endl;
    }).router([](MiddlewareRouter& router) {
        router.route(Request::Method::GET, "/leds/$", [](MiddlewareChain& chain) {
            chain.useFunc([](Request& req, Response& res, const auto& next) {
                std::cout << "BEGIN [GET /leds/:name]" << std::endl;
                auto name = req.getParameter(0);
                next();
                std::cout << "END [GET /leds/:name]" << std::endl;
            });
        }).route(Request::Method::POST, "/leds/$/$", [](MiddlewareChain& chain) {
            chain.useFunc([](Request& req, Response& res, const auto& next) {
                std::cout << "BEGIN [POST /leds/:name/:state]" << std::endl;
                auto name = req.getParameter(0);
                auto state = req.getParameter(1);
                next();
                std::cout << "END [POST /leds/:name/:state]" << std::endl;
            });
        });
    }).useFunc([](Request&, Response&, const auto&) {
        std::cout << "FINAL" << std::endl;
    });

    std::fstream getStream("../samples/get.dump");
    std::fstream postStream("../samples/post.dump");
    StreamConnection getConn(getStream);
    StreamConnection postConn(postStream);
    app.handle(getConn);
    app.handle(postConn);

    return 0;
}
