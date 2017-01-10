#pragma once

#include "connection.h"

#include <iostream>

namespace lighttpning {

    class StreamConnection : public Connection {
    public:
        StreamConnection(std::istream& in, std::ostream& out);
        StreamConnection(std::iostream& inout);

        size_t read(char* buffer, const size_t length) override;
        size_t read(char* buffer, const size_t length, const char delimiter) override;
        size_t skip(const size_t length) override;
        size_t skip(const size_t length, const char delimiter) override;
        bool connected() override;

        size_t write(const char* buffer, const size_t length) override;
        void close() override;

    private:
        std::istream& input;
        std::ostream& output;
        bool isConnected = true;
    };

}
