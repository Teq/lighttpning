#pragma once

#include <cstdlib>

namespace lighttpning {

    class StringView {

    public:

        StringView(const char* buffer, size_t size);

        size_t size() const;

        const char* view() const;

    private:

        const char* viewPtr;
        const size_t viewSize;
    };

}
