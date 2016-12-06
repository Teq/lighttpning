#pragma once

#include "../http/request.h"
#include "../http/response.h"

namespace lighttpning {

    class Middleware {

        friend class MiddlewareNode;
        friend class MiddlewareChain;
        friend class MiddlewareRouter;

    public:

        virtual ~Middleware() { }

    protected:

        Middleware();

        void setNext(const Middleware* middleware);

        virtual void call(Request& request, Response& response) const = 0;

        const Middleware* next = nullptr;
    };

    class : public Middleware {
    protected:
        void call(Request&, Response&) const override { }
    } FINAL;

    class Next {
    public:
        virtual void operator() () const = 0;
    };
}
