#pragma once

#include <cstdlib>

namespace Lighttpning {

    class StringBuffer { // TODO: Implement according to The Rule Of Three/Four

    public:

        // ctors, assignment operators, dtor

        StringBuffer() = default;

        StringBuffer(size_t capacity);

        StringBuffer(const StringBuffer& other); // copy

        StringBuffer(StringBuffer&& other); // move

        StringBuffer& operator =(StringBuffer other); // copy-and-swap

        StringBuffer& operator =(StringBuffer&& other); // move assignment

        ~StringBuffer();

        // methods

//        void operator += (char character);

//        void operator += (const char* string);

        bool operator ==(const StringBuffer&) const;

        bool operator ==(const char*) const;

        bool empty() const;

        void clear();

        size_t capacity() const;

        void reserve(size_t newCapacity);

        void shrink();

        size_t size() const;

        bool resize(size_t newSize);

        char* buff() const;

    private:

        size_t bufferCapacity = 0;
        size_t bufferSize = 0;
        char* buffer = nullptr;

    };


}

