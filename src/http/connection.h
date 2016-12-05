#pragma once

namespace lighttpning {

    class ConnectionIn {
    public:
        virtual char read(uint16_t timeout) = 0;
        virtual size_t read(char* buffer, size_t length, uint16_t timeout) = 0;
        virtual size_t read(char untilChar, char* buffer, size_t length, uint16_t timeout) = 0;
    };

    class ConnectionOut {
    public:
        virtual void write(char c, uint16_t timeout) = 0;
        virtual size_t write(char* buffer, size_t length, uint16_t timeout) = 0;
    };

    class Connection : public ConnectionIn, public ConnectionOut { };

}
