#include "stream_connection.h"

namespace lighttpning {

    StreamConnection::StreamConnection(std::istream& in, std::ostream& out):
        input(in), output(out)
    { }  
  
    size_t StreamConnection::read(char* buffer, size_t length) {
        input.read(buffer, length);
        return input.gcount();
    }

    size_t StreamConnection::read(const char delimiter, char* buffer, size_t length) {
        input.get(buffer, length, delimiter);
        size_t count = input.gcount();
        buffer[count] = delimiter;
        return count + 1;
    }

    bool StreamConnection::connected() {
        return isConnected;
    }
    
    size_t StreamConnection::write(char* buffer, size_t length) {
        throw std::logic_error("Not implemented");
    }

    void StreamConnection::close() {
        isConnected = false;
    }

}
