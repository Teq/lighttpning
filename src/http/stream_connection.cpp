#include "stream_connection.h"

namespace Lighttpning {

    StreamConnection::StreamConnection(std::istream& in, std::ostream& out):
        input(in),
        output(out)
    { }

    StreamConnection::StreamConnection(std::iostream& inout):
        input(inout),
        output(inout)
    { }

    size_t StreamConnection::read(char* buffer, const size_t length) {
        input.read(buffer, length);
        return (size_t)input.gcount();
    }

    size_t StreamConnection::read(char* buffer, const size_t length, const char delimiter) {
        size_t size = 0;
        for (;size < length;) {
            char ch = (char)input.get();
            if (input.eof()) {
                break;
            }
            buffer[size++] = ch;
            if (ch == delimiter) {
                break;
            }
        }
        return size;
    }

    size_t StreamConnection::skip(const size_t length) {
        input.ignore(length);
        return (size_t)input.gcount();
    }

    size_t StreamConnection::skip(const size_t length, const char delimiter) {
        input.ignore(length, delimiter);
        return (size_t)input.gcount();
    }

    bool StreamConnection::connected() {
        return isConnected;
    }
    
    size_t StreamConnection::write(const char* buffer, size_t length) {
        return 0;
    }

    void StreamConnection::close() {
        isConnected = false;
    }

}
