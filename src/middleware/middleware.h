#pragma once

#include "../http/request.h"
#include "../http/response.h"

namespace lighttpning {

    class Middleware {
    public:
        virtual ~Middleware() { }

        virtual void call(Request& request, Response& response) const = 0;
        virtual void setNext(const Middleware& middleware) = 0;
    };

    class : public Middleware {
    public:
        void call(Request&, Response&) const override { }
        void setNext(const Middleware&) override { }
    } FINAL;

    class Next {
    public:
        virtual void operator() () const = 0;
    };
}
