#include "string_buffer.h"
#include "exceptions/runtime_error.h"

#include <cstring>

namespace Lighttpning {

    StringBuffer::StringBuffer(size_t capacity)
    {
        reserve(capacity);
    }

//    StringBuffer::StringBuffer(const StringBuffer& other)
//    {
//        // NOTE: For new buffer we allocate other.bufferSize, but NOT other.bufferCapacity
//        reserve(other.bufferSize);
//        memcpy(buffer, other.buffer, other.bufferSize);
//    }

//    StringBuffer& StringBuffer::operator =(StringBuffer other) {
//        return *this;
//    }

    StringBuffer::~StringBuffer() {
        free(buffer);
    }

    bool StringBuffer::empty() const {
        return bufferSize == 0;
    }

    void StringBuffer::clear() {
        bufferSize = 0;
    }

    void StringBuffer::operator += (const char ch) {
        if (bufferCapacity == bufferSize) {
            reserve(bufferCapacity + 1);
        }
        buffer[bufferSize++] = ch;
    }

    void StringBuffer::operator += (const char* cStr) {
        size_t lenght = strlen(cStr);
        if (bufferSize + lenght >= bufferCapacity) {
            reserve(bufferSize + lenght);
        }
        memcpy(buffer + bufferSize, cStr, lenght);
        bufferSize += lenght;
    }

    bool StringBuffer::operator == (const StringBuffer& other) const {
        return strncmp(buffer, other.buff(), bufferSize) == 0;
    }

    bool StringBuffer::operator == (const char* other) const {
        return strncmp(buffer, other, bufferSize) == 0;
    }

    size_t StringBuffer::capacity() const {
        return bufferCapacity;
    }

    void StringBuffer::reserve(size_t newCapacity) {

        if (newCapacity > 0) {

            char* newBuffer = (char*)realloc(buffer, newCapacity);

            if (newBuffer == nullptr) {
                throw RuntimeError::OutOfMemory();
            }

            buffer = newBuffer;

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

    char* StringBuffer::buff() const {
        return buffer;
    }

}
