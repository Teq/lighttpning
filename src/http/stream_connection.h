#pragma once

#include <iostream>

#include "connection.h"

namespace lighttpning {

    class StreamConnection : public Connection {
    public:
        StreamConnection(std::istream& in, std::ostream& out);

        char read(uint16_t timeout) override;
        size_t read(char *buffer, size_t length, uint16_t timeout) override;
        size_t read(char untilChar, char *buffer, size_t length, uint16_t timeout) override;
        void write(char c, uint16_t timeout) override;
        size_t write(char *buffer, size_t length, uint16_t timeout) override;

    private:
        std::istream& input;
        std::ostream& output;
    };

}
