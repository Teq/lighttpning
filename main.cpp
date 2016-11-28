#include <iostream>
#include <fstream>
#include "application.h"
#include "putchar_adapter.h"

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

    char c;
    PutcharAdapter parser;
    std::ifstream sample("../samples/get.dump");
    while (sample.get(c)) {
        std::cout << c;
        auto ctx = parser.putchar(c);
        if (ctx) {
            app.request(*ctx);
        }

    }

    return 0;
}
