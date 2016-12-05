#include "stream_connection.h"

namespace lighttpning {

    StreamConnection::StreamConnection(std::istream& in, std::ostream& out):
        input(in), output(out)
    { }  
  
    char StreamConnection::read(uint16_t timeout) {
        char ch;
        input.get(ch);
        return ch;
    }

    size_t StreamConnection::read(char *buffer, size_t length, uint16_t timeout) {
        return 0;
    }

    size_t StreamConnection::read(char untilChar, char *buffer, size_t length, uint16_t timeout) {
        return 0;
    }

    void StreamConnection::write(char c, uint16_t timeout) {

    }

    size_t StreamConnection::write(char *buffer, size_t length, uint16_t timeout) {
        return 0;
    }

}
