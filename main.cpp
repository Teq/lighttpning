#include <iostream>
#include "lighttpning.h"

using namespace Lighttpning;

int main() {

    Application app;

//    Router router;
//    router.get("/", [](const Request& req, Response& res, const Middleware& next) -> void {
//        next.call();
//    });
//
//    app.use(router);

    app.use([](HttpContext& ctx, const Next& next) {
        std::cout << "BEGIN 1" << std::endl;
        next();
        std::cout << "END 1" << std::endl;
    });

    app.use([](HttpContext& ctx, const Next& next) {
        std::cout << "BEGIN 2" << std::endl;
        next();
        std::cout << "END 2" << std::endl;
    });

    app.use([](HttpContext& ctx, const Next& next) {
        std::cout << "BEGIN 3" << std::endl;
        next();
        std::cout << "END 3" << std::endl;
    });

    HttpContext ctx;
    app.request(ctx);

    return 0;
}
