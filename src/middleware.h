#pragma once

#include "http/request.h"
#include "http/response.h"

namespace lighttpning {

    /**
     * Internal class which represents a middleware
     */
    class Middleware {
    public:
        virtual ~Middleware() { }
        virtual void call(Request&, Response&) const = 0;
        virtual void setNext(const Middleware&) = 0;
    };

    class : public Middleware {
    public:
        void call(Request&, Response&) const override { }
        void setNext(const Middleware&) override { }
    } final;

    class Next {
    public:
        virtual void operator() () const = 0;
    };

    class NextImpl : public Next {
    public:
        NextImpl (const Middleware& middleware, Request& request, Response& response) :
            middleware(middleware),
            request(request),
            response(response)
        { }

        void operator() () const override {
            middleware.call(request, response);
        }

    private:
        const Middleware& middleware;
        Request& request;
        Response& response;
    };

    using MiddlewareFunction = void (*)(Request& req, Response& res, const Next& next);

    class MiddlewareImpl : public Middleware {
    public:

        MiddlewareImpl(const MiddlewareFunction& middlewareFunction)
                : func(middlewareFunction),
                  next(&final) { }

        void call(Request& request, Response& response) const override {
            NextImpl nextFunctor(*next, request, response);
            func(request, response, nextFunctor);
        }

        void setNext(const Middleware& middleware) override {
            next = &middleware;
        }

    private:
        const Middleware* next = nullptr;
        const MiddlewareFunction& func;
    };
}
