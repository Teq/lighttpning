#include <fstream>

#include "src/application.h"
#include "src/router.h"
#include "src/http/stream_connection.h"

using namespace lighttpning;

int main() {
    
    Application app;

    app.use([](Request& req, Response& res, const Next& next) {
        std::cout << "BEGIN [pre]" << std::endl;
        next();
        std::cout << "END [pre]" << std::endl;
    });

//     Router router;
//     router.use(Request::Method::GET, "/stat", [](Request& req, Response& res, const Next& next) {
//         std::cout << "BEGIN [stat]" << std::endl;
//         next();
//         std::cout << "END [stat]" << std::endl;
//     });
//     app.use(router);

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
