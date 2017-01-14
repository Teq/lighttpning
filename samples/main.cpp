#include <fstream>
#include <string>

#include "request_handler.h"
#include "http/stream_connection.h"

using namespace Lighttpning;

class Functor { // for tests

    int val;

    std::basic_ostream<std::string::value_type, std::string::traits_type>& log() const {
        return std::cout << "<<" << (size_t)this << ">>, val = " << val << ", ";
    }

public:

    //ctor
    Functor(int n): val(n) {
        log() << "CONSTRUCTOR" << std::endl;
    }
    Functor(const Functor& other) {
        val = other.val;
        log() << "COPY CONSTRUCTOR" << std::endl;
    }
    Functor(Functor&& other) {
        val = other.val;
        other.val = 0;
        log() << "MOVE CONSTRUCTOR" << std::endl;
    }

    //dtor
    ~Functor() {
        log() << "DESTRUCTOR" << std::endl;
        val = 0;
    }

    //assy
    Functor& operator =(Functor other) {
        val = other.val;
        log() << "COPY ASSY (1)" << std::endl;
        return *this;
    }
    Functor& operator =(const Functor& other) {
        val = other.val;
        log() << "COPY ASSY (2)" << std::endl;
        return *this;
    }

    //methods
    void operator ()(Request& req, Response& res, const Middleware::Next& next) const {
        log() << "EXEC" << std::endl;
        next();
    }
};

int main() {

//    std::cout << std::is_base_of<Middleware, MiddlewareFunction<int>>::value << std::endl;

    RequestHandler app;

//    Functor f(23);

    app.use(Functor(45)).use([](Request& req, Response& res, const Middleware::Next& next) {
        auto path = req.getPath();
        std::cout << "BEGIN " + std::string(path.view(), path.size()) << std::endl;
        next();
        std::cout << "END" << std::endl;
    }).router([](Router& router) {
        router.route(Request::Method::GET, "/leds/$", [](MiddlewareChain& chain) {
            chain.use([](Request& req, Response& res, const Middleware::Next& next) {
                std::cout << "ROUTE [GET /leds/$] " << std::endl;
                next();
            });
        }).route(Request::Method::POST, "/leds/$/$", [](MiddlewareChain& chain) {
            chain.use([](Request& req, Response& res, const Middleware::Next& next) {
                std::cout << "ROUTE [POST /leds/$/$] " << std::endl;
                next();
            });
        });
    });

    std::fstream getStream("samples/get.dump");
    std::fstream postStream("samples/post.dump");
    StreamConnection getConn(getStream);
    StreamConnection postConn(postStream);
    app.handle(getConn);
    app.handle(postConn);

    return 0;
}
