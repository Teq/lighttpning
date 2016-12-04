#pragma once

namespace Lighttpning {

    /**
     * Represents network connection
     */
    class IConnection {
    public:

        virtual char readByte(uint16_t timeout) = 0;
        virtual size_t readBytes(char* buffer, size_t length, uint16_t timeout) = 0;


        virtual void writeChar(char c) = 0;
    };

}
