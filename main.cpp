#include <fstream>

#include "src/lighttpning.h"
#include "src/http/stream_connection.h"

using namespace lighttpning;
using Next = MiddlewareFunction::Next;


int main() {

    Lighttpning app;

    MiddlewareRouter router;

    router.route(Request::Method::GET, "/leds/:name").use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [GET /leds/:name]" << std::endl;
        next();
        std::cout << "END [GET /leds/:name]" << std::endl;
    });

    router.route(Request::Method::POST, "/leds/:name/:state").use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [POST /leds/:name/:state]" << std::endl;
        next();
        std::cout << "END [POST /leds/:name/:state]" << std::endl;
    });

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
    StreamConnection postConn(postStream);
    app.handle(getConn);
    app.handle(postConn);

    return 0;
}
