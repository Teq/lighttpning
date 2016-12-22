#pragma once

#include <cstdlib>

namespace lighttpning {

    class StringView {

    public:

        StringView(const char* buffer, size_t size);

        StringView(const char* cStr);

        size_t size() const;

        const char* view() const;

        bool includes(const char *ptr) const;

    private:

        const char* viewPtr;
        const size_t viewSize;
    };

}
