#include "string_view.h"

#include <cstring>

namespace Lighttpning {

    StringView::StringView(const char* buffer, size_t size):
        viewPtr(buffer),
        viewSize(size)
    { }

    StringView::StringView(const char* cStr):
        StringView(cStr, strlen(cStr))
    { }

    size_t StringView::size() const {
        return viewSize;
    }

    const char* StringView::view() const {
        return viewPtr;
    }

    bool StringView::includes(const char *ptr) const {
        return viewPtr <= ptr && ptr < (viewPtr + viewSize);
    }
}
