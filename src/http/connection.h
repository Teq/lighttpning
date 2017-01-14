#pragma once

#include <cstdlib>

namespace Lighttpning {

    class ConnectionIn {

    public:

        /**
         * Read characters from client until \p length characters were read or EOF reached
         * @param buffer Buffer to read to
         * @param length Maximum number of characters to read
         * @return The actual number of characters that have been read
         */
        virtual size_t read(char* buffer, const size_t length) = 0;

        /**
         * Read characters from client until one of the following occurs:
         * - \p delimiter character reached (which is included in resulting \p buffer)
         * - \p length characters were read
         * - EOF reached
         * @param buffer Buffer to read to
         * @param length Maximum number of characters to read
         * @param delimiter Character to look for
         * @return The actual number of characters that have been read
         */
        virtual size_t read(char* buffer, const size_t length, const char delimiter) = 0;

        /**
         * Skip characters from client until \p length characters were skipped or EOF reached
         * @param length Maximum number of characters to skip
         * @return The actual number of characters that have been skipped
         */
        virtual size_t skip(const size_t length) = 0;

        /**
         * Skip characters from client until one of the following events occurs:
         * - \p delimiter character reached (which is skipped as well)
         * - \p length characters were skipped
         * - EOF reached
         * @param length Maximum number of characters to skip
         * @param delimiter Delimiter character
         * @return The actual number of characters that have been skipped
         */
        virtual size_t skip(const size_t length, const char delimiter) = 0;

        /**
         * @return True if connection is active
         */
        virtual bool connected() = 0;

    };

    class ConnectionOut {

    public:

        /**
         * Send characters to client
         * @param buffer Buffer to send
         * @param length Buffer length
         * @return
         */
        virtual size_t write(const char* buffer, const size_t length) = 0;

        /**
         * Close client connection. No further read/write operations will be possible.
         */
        virtual void close() = 0;
    };

    class Connection : public ConnectionIn, public ConnectionOut { };

}
