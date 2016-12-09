#pragma once

#include <functional>

#include "middleware.h"

namespace lighttpning {

    class MiddlewareFunction : public Middleware {

    public:

        using Next = std::function<void()>;

        using Function = std::function<void(Request&, Response&, const Next&)>;

        MiddlewareFunction(const Function&);

        void call(Request&, Response&) const override;

    private:

        const Function func;

    };

}
