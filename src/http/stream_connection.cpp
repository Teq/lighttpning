#include "stream_connection.h"

namespace lighttpning {

    StreamConnection::StreamConnection(std::istream& in, std::ostream& out):
        input(in),
        output(out)
    { }

    StreamConnection::StreamConnection(std::iostream& inout):
        input(inout),
        output(inout)
    { };

    size_t StreamConnection::read(char* buffer, size_t length) {
        input.read(buffer, length);
        return (size_t)input.gcount();
    }

    size_t StreamConnection::read(const char delimiter, char* buffer, size_t length) {
        input.get(buffer, length, delimiter);
        size_t size = (size_t)input.gcount();
        buffer[size] = delimiter;
        return size + 1;
    }

    size_t StreamConnection::ignore(size_t length) {
        input.ignore(length);
        return (size_t)input.gcount();
    }

    size_t StreamConnection::ignore(const char delimiter, size_t length) {
        input.ignore(length, delimiter);
        return (size_t)input.gcount();
    }

    bool StreamConnection::connected() {
        return isConnected;
    }
    
    size_t StreamConnection::write(char* buffer, size_t length) {
        return 0;
    }

    void StreamConnection::close() {
        isConnected = false;
    }

}
