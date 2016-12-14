#include <fstream>

#include "src/lighttpning.h"
#include "src/http/stream_connection.h"

using namespace lighttpning;
using Next = MiddlewareFunction::Next;

void handler1(Request& req, Response& res, const Next& next) {
    std::cout << "BEGIN [GET /leds/:name]" << std::endl;
    next();
    std::cout << "END [GET /leds/:name]" << std::endl;
}

void handler2(Request& req, Response& res, const Next& next) {
    std::cout << "BEGIN [POST /leds/:name/:state]" << std::endl;
    next();
    std::cout << "END [POST /leds/:name/:state]" << std::endl;
}

int main() {

    Lighttpning app;
    MiddlewareRouter router;

    router.route(Request::Method::GET, "/leds/:name").use(handler1);
    router.route(Request::Method::POST, "/leds/:name/:state").use(handler2);
//     router.route(Request::Method::POST, "/leds/:name/:state", [](MiddlewareChain& chain) {
//         chain.use(handler2);
//     });

    app.use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN" << std::endl;
        next();
        std::cout << "END" << std::endl;
    }).use(router).use([](Request&, Response&, const Next&) {
        std::cout << "FINAL" << std::endl;
    });

    std::fstream getStream("../samples/get.dump");
    std::fstream postStream("../samples/post.dump");
    StreamConnection getConn(getStream);
    StreamConnection connPost(postStream);
    app.handle(getConn);
    app.handle(connPost);

    return 0;
}
