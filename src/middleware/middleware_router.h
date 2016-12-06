#pragma once

#include "middleware_node.h"

namespace lighttpning {

    class MiddlewareRouter : public Middleware {
        void call(Request&, Response&) const override;
    };
}
