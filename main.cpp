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

    app.use([](const Request& req, Response& res, const Middleware& next) -> void {
        std::cout << "BEGIN 1" << std::endl;
        next.call();
        std::cout << "END 1" << std::endl;
    });

    app.use([](const Request& req, Response& res, const Middleware& next) -> void {
        std::cout << "BEGIN 2" << std::endl;
        next.call();
        std::cout << "END 2" << std::endl;
    });

    app.use([](const Request& req, Response& res, const Middleware& next) -> void {
        std::cout << "BEGIN 3" << std::endl;
        next.call();
        std::cout << "END 3" << std::endl;
    });

    app.request();

    return 0;
}
