#include <fstream>

#include "src/application.h"
#include "src/middleware/middleware_router.h"
#include "src/http/stream_connection.h"

using namespace lighttpning;
using Next = MiddlewareFunction::Next;

int main() {
    
    Application app, app2;
    
    app.use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [1]" << std::endl;
        auto asd = req.getMethod();
        next();
        std::cout << "END [1]" << std::endl;
    }).use(app2).use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [2]" << std::endl;
        next();
        std::cout << "END [2]" << std::endl;
    });
    
    app2.use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [1a]" << std::endl;
        next();
        std::cout << "END [1a]" << std::endl;
    }).use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [1b]" << std::endl;
        next();
        std::cout << "END [1b]" << std::endl;
    });

    MiddlewareRouter router;
    router.match(Request::Method::GET, "/stat/:param1").use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [stat]" << std::endl;
        auto param1 = req.getParameter("param1");
        next();
        std::cout << "END [stat]" << std::endl;
    });
    router.match(Request::Method::POST, "/options/:name/:value").use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [opts_step1]" << std::endl;
        auto name = req.getParameter("name");
        auto value = req.getParameter("value");
        next();
        std::cout << "END [opts_step1]" << std::endl;
    }).use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [opts_step2]" << std::endl;
        next();
        std::cout << "END [opts_step2]" << std::endl;
    });

    app.use(router).use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [3]" << std::endl;
        next();
        std::cout << "END [3]" << std::endl;
    });

    std::fstream sample("../samples/get.dump");
    StreamConnection conn(sample, sample);
    app.handle(conn);

    return 0;
}
