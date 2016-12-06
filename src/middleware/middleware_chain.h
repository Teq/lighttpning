#pragma once

#include <vector>

#include "middleware_node.h"
#include "middleware_node.h"

namespace lighttpning {

    class MiddlewareChain : public Middleware {
    public:
        MiddlewareChain();
        void use(Middleware&);
        void use(const MiddlewareFunction&);
        void call(Request&, Response&) const override;
        void setNext(const Middleware&) override;
    protected:
        std::vector<Middleware*> chain;
    private:
        const Middleware* next = nullptr;
    };

}
