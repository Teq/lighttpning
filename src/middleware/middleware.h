#pragma once

#include <functional>

#include "../http/request.h"
#include "../http/response.h"

namespace lighttpning {

    class Middleware {

        friend class MiddlewareChain;

    public:

        using Next = std::function<void()>;

        using Function = std::function<void(Request&, Response&, const Next&)>;

        Middleware(const Function&);

    protected:

        void call(Request&, Response&) const;

        const Middleware* next = nullptr;

    private:

        const Function func;

    };

}
