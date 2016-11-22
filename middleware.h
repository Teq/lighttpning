#pragma once

#include "httpcontext.h"

namespace Lighttpning {

    class Middleware {
    public:
        virtual ~Middleware() { }
        virtual void call() const = 0;
        virtual void setNext(const Middleware&) = 0;
    };

    using MiddlewareFunc = void (*)(const Request& req, Response& res, const Middleware& next);

    class MiddlewareImpl : public Middleware {
    public:

        MiddlewareImpl(const MiddlewareFunc& middlewareFunc) : func(middlewareFunc) { }

        virtual void call() const {
            if (next) {
                func(req, res, *next);
            }
        }

        virtual void setNext(const Middleware& middleware) {
            next = &middleware;
        }

    private:
        const Middleware* next = nullptr;
        const MiddlewareFunc func = nullptr;

        Request req;
        Response res;
    };

    class MiddlewareFinal : public Middleware {
    public:
        virtual void call() const { }
        virtual void setNext(const Middleware& middleware) { }
    };

}
