#pragma once

#include "middleware.h"

namespace lighttpning {
    
    class Router : public Middleware {
        void call(Request&, Response&) const override;
        void setNext(const Middleware&) override;
    };
}
