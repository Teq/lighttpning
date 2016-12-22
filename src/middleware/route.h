#pragma once

#include "../http/request.h"
#include "../misc/string_view.h"

namespace lighttpning {

    class Route {

    public:

        Route(Request::Method, StringView pattern);

        bool match(Request&) const;

    private:

        Request::Method method;
        StringView pattern;

    };

}
