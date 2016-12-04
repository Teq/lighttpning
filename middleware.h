#pragma once

#include "http_context.h"

namespace Lighttpning {

    /**
     * Internal class which represents a middleware
     */
    class Middleware {
    public:
        virtual ~Middleware() { }
        virtual void call(HttpContext&) const = 0;
        virtual void setNext(const Middleware&) = 0;
    };

    class : public Middleware {
    public:
        virtual void call(HttpContext&) const { }
        virtual void setNext(const Middleware& middleware) { }
    } final;

    class Next {
    public:
        virtual void operator() () const = 0;
    };

    class NextImpl : public Next {
    public:
        NextImpl (const Middleware& _middleware, HttpContext& _context)
                : middleware(_middleware),
                  context(_context) { }

        virtual void operator() () const {
            middleware.call(context);
        }

    private:
        const Middleware& middleware;
        HttpContext& context;
    };

    using MiddlewareFunction = void (*)(HttpContext& ctx, const Next& next);

    class MiddlewareImpl : public Middleware {
    public:

        MiddlewareImpl(const MiddlewareFunction& middlewareFunction)
                : func(middlewareFunction),
                  next(&final) { }

        virtual void call(HttpContext& context) const {
            NextImpl nextFunctor(*next, context);
            func(context, nextFunctor);
        }

        virtual void setNext(const Middleware& middleware) {
            next = &middleware;
        }

    private:
        const Middleware* next = nullptr;
        const MiddlewareFunction& func;
    };
}
