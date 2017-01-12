#pragma once

#include <cstdlib>

namespace lighttpning {

    class StringBuffer { // TODO: Implement according The Rule Of Three/Four

    public:

        // constructor

        StringBuffer();

        StringBuffer(size_t capacity);

        //StringBuffer(const StringBuffer& other);

        ~StringBuffer();

//        void operator += (char character);

//        void operator += (const char* string);

        bool operator ==(const StringBuffer&) const;

        bool operator ==(const char*) const;

        bool empty() const;

        void clear();

        size_t capacity() const;

        bool reserve(size_t newCapacity);

        bool shrink();

        size_t size() const;

        bool resize(size_t newSize);

        char* buff() const;

    private:

        size_t bufferCapacity = 0;
        size_t bufferSize = 0;
        char* buffer = nullptr;

    };


}

