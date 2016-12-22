#include <fstream>
#include <string>

#include "../src/lighttpning.h"
#include "../src/http/stream_connection.h"

using namespace lighttpning;

std::string format(const std::vector<StringView>& parameters) {
    std::string result;


    return result;
}

int main() {

    Lighttpning app;

    app.useFunc([](Request& req, Response& res, const auto& next) {
        auto path = req.getPath();
        std::cout << "BEGIN " + std::string(path.view(), path.size()) << std::endl;
        next();
        std::cout << "END" << std::endl;
    }).router([](MiddlewareRouter& router) {
        router.route(Request::Method::GET, "/leds/$", [](MiddlewareChain& chain) {
            chain.useFunc([](Request& req, Response& res, const auto& next) {
                std::cout << "ROUTE [GET /leds/$] " + format(req.getParameters()) << std::endl;
                next();
            });
        }).route(Request::Method::POST, "/leds/$/$", [](MiddlewareChain& chain) {
            chain.useFunc([](Request& req, Response& res, const auto& next) {
                std::cout << "ROUTE [POST /leds/$/$] " + format(req.getParameters()) << std::endl;
                next();
            });
        });
    });

    std::fstream getStream("../samples/get.dump");
    std::fstream postStream("../samples/post.dump");
    StreamConnection getConn(getStream);
    StreamConnection postConn(postStream);
    app.handle(getConn);
    app.handle(postConn);

    return 0;
}
