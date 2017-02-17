#include "string_buffer.h"
#include "exceptions/runtime_error.h"

#include <cstring>

namespace Lighttpning {

    StringBuffer::StringBuffer(size_t capacity) {
        reserve(capacity);
    }

    StringBuffer::~StringBuffer() {
        free(bufferPtr);
    }

    StringBuffer::StringBuffer(StringBuffer&& other) {
        bufferPtr = other.bufferPtr;
        bufferCapacity = other.bufferCapacity;
        bufferSize = other.bufferSize;
        other.bufferPtr = nullptr;
        other.bufferCapacity = 0;
        other.bufferSize = 0;
    }

    bool StringBuffer::empty() const {
        return bufferSize == 0;
    }

    void StringBuffer::clear() {
        bufferSize = 0;
    }

    void StringBuffer::operator += (const char ch) {
        size_t newSize = bufferSize + 1;
        if (bufferCapacity < newSize) {
            reserve(newSize);
        }
        bufferSize = newSize;
        bufferPtr[bufferSize] = ch;
    }

    void StringBuffer::operator += (const char* cStr) {
        size_t lenght = strlen(cStr);
        size_t newSize = bufferSize + lenght;
        if (bufferCapacity < newSize) {
            reserve(newSize);
        }
        memcpy(bufferPtr + bufferSize, cStr, lenght);
        bufferSize = newSize;
    }

    bool StringBuffer::operator == (const StringBuffer& other) const {
        return strncmp(bufferPtr, other.ptr(), bufferSize) == 0;
    }

    bool StringBuffer::operator == (const char* other) const {
        return strncmp(bufferPtr, other, bufferSize) == 0;
    }

    size_t StringBuffer::capacity() const {
        return bufferCapacity;
    }

    void StringBuffer::reserve(size_t newCapacity) {

        if (newCapacity > 0) {

            char* newBuffer = (char*)realloc(bufferPtr, newCapacity);

            if (newBuffer == nullptr) {
                throw RuntimeError::OutOfMemory();
            }

            bufferPtr = newBuffer;

            bufferCapacity = newCapacity;
            if (bufferSize > bufferCapacity) {
                bufferSize = bufferCapacity;
            }

        } else { // newCapacity =< 0
            throw RuntimeError::BadArgument();
        }

    }

    void StringBuffer::shrink() {
        return reserve(bufferSize);
    }

    size_t StringBuffer::size() const {
        return bufferSize;
    }

    void StringBuffer::resize(size_t newSize) {

        if (newSize > bufferCapacity) {
            reserve(newSize);
        }

        bufferSize = newSize;
    }

    char* StringBuffer::ptr() const {
        return bufferPtr;
    }

}
