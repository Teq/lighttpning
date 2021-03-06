#pragma once

#include "http/request.h"
#include "misc/string_view.h"

namespace Lighttpning {

    class Route {

    public:

        Route(Request::Method, StringView&& pattern);

        bool match(Request&) const;

    private:

        const Request::Method method;
        const StringView pattern;

    };

}
