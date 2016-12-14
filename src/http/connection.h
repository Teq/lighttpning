#pragma once

namespace lighttpning {

    class ConnectionIn {
    public:
        virtual size_t read(char* buffer, size_t length) = 0;
        virtual size_t read(const char delimiter, char* buffer, size_t length) = 0;
        virtual bool connected() = 0;
    };

    class ConnectionOut {
    public:
        virtual size_t write(char* buffer, size_t length) = 0;
        virtual void close() = 0;
    };

    class Connection : public ConnectionIn, public ConnectionOut { };

}
