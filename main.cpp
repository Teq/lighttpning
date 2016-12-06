#include <fstream>

#include "src/application.h"
#include "src/middleware/middleware_router.h"
#include "src/http/stream_connection.h"

using namespace lighttpning;

int main() {
    
    Application app;

    app.use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [pre]" << std::endl;
        auto asd = req.getMethod();
        next();
        std::cout << "END [pre]" << std::endl;
    });

//    MiddlewareRouter router;
//    router.match(Request::Method::GET, "/stat").use([](Request& req, Response& res, const Next& next) {
//        std::cout << "BEGIN [stat]" << std::endl;
//        next();
//        std::cout << "END [stat]" << std::endl;
//    });
//    router.match(Request::Method::POST, "/options").use([](Request& req, Response& res, const Next& next) {
//        std::cout << "BEGIN [opts_step1]" << std::endl;
//        next();
//        std::cout << "END [opts_step1]" << std::endl;
//    }).use([](Request& req, Response& res, const Next& next) {
//        std::cout << "BEGIN [opts_step2]" << std::endl;
//        next();
//        std::cout << "END [opts_step2]" << std::endl;
//    });
//    app.use(router);

    app.use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [post]" << std::endl;
        next();
        std::cout << "END [post]" << std::endl;
    });

    std::fstream sample("../samples/get.dump");
    StreamConnection conn(sample, sample);
    app.handle(conn);

    return 0;
}
