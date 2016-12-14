#pragma once

#include <iostream>

#include "connection.h"

namespace lighttpning {

    class StreamConnection : public Connection {
    public:
        StreamConnection(std::istream& in, std::ostream& out);
        StreamConnection(std::iostream& inout);

        size_t read(char* buffer, size_t length) override;
        size_t read(const char delimiter, char* buffer, size_t length) override;
        bool connected() override;

        size_t write(char* buffer, size_t length) override;
        void close() override;

    private:
        std::istream& input;
        std::ostream& output;
        bool isConnected = true;
    };

}
