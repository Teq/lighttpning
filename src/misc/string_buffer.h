#pragma once

#include <cstdlib>

namespace Lighttpning {

    class StringBuffer { // TODO: Implement according to The Rule Of Three/Four

    public:

        StringBuffer() = default;
        StringBuffer(size_t capacity);
        ~StringBuffer();

        // non-copyable
        StringBuffer(const StringBuffer&) = delete;
        StringBuffer& operator = (const StringBuffer&) = delete;

        // movable, but not move-assignable
        StringBuffer(StringBuffer&&);
        StringBuffer& operator = (StringBuffer&&) = delete;

        /**
         * @brief Append character to the buffer
         */
        void operator += (const char);

        /**
         * @brief Append C-string to the buffer
         */
        void operator += (const char*);

        /**
         * @return True if buffer content is equal to content of other buffer
         */
        bool operator == (const StringBuffer&) const;

        /**
         * @return True if buffer content is equal to content of C-string
         */
        bool operator == (const char*) const;

        /**
         * @return True if buffer size is zero
         */
        bool empty() const;

        /**
         * @brief Set buffer size to zero.
         */
        void clear();

        /**
         * @return Buffer capacity
         */
        size_t capacity() const;

        /**
         * @brief Change buffer capacity
         * In case if \p newCapacity is less than buffer size, the latter is reduced to match \p newCapacity
         * @param newCapacity
         */
        void reserve(size_t newCapacity);

        /**
         * @brief Shrink buffer capacity to match buffer size
         */
        void shrink();

        /**
         * @return Buffer size
         */
        size_t size() const;

        /**
         * @brief Change buffer size
         * In case if \p newSize is more than buffer capacity, the latter is increased to fit \p newSize
         * @param newSize
         */
        void resize(size_t newSize);

        /**
         * @return Pointer to internal buffer
         */
        char* ptr() const;

    private:

        size_t bufferCapacity = 0;
        size_t bufferSize = 0;
        char* bufferPtr = nullptr;

    };


}

