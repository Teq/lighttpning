#include "request.h"

namespace lighttpning {

    Request::Request(ConnectionIn& in):
        connection(in),
        requestLineBuffer(DEFAULT_STR_BUFF_SIZE),
        headerLineBuffer(DEFAULT_STR_BUFF_SIZE)
    { }
    
    Request::Method Request::getMethod() {
        
        if (method == Method::UNKNOWN) {

            // read until space
            size_t size = connection.read(requestLineBuffer.buff(), MAX_HTTP_METHOD_STR_SIZE, ' ');
            // set actual size (excluding space character)
            requestLineBuffer.resize(size - 1);

            if (requestLineBuffer == "OPTIONS") {
                method = Method::OPTIONS;
            } else if (requestLineBuffer == "GET") {
                method = Method::GET;
            } else if (requestLineBuffer == "HEAD") {
                method = Method::HEAD;
            } else if (requestLineBuffer == "POST") {
                method = Method::POST;
            } else if (requestLineBuffer == "PUT") {
                method = Method::PUT;
            } else if (requestLineBuffer == "PATCH") {
                method = Method::PATCH;
            } else if (requestLineBuffer == "DELETE") {
                method = Method::DELETE;
            } else if (requestLineBuffer == "TRACE") {
                method = Method::TRACE;
            } else if (requestLineBuffer == "CONNECT") {
                method = Method::CONNECT;
            }

            requestLineBuffer.clear();

        }
        
        return method;
    }

    const StringView Request::getPath() {

        getMethod(); // ensure HTTP method is parsed

        if (requestLineBuffer.empty()) {

            // read until space
            size_t size = connection.read(requestLineBuffer.buff(), MAX_HTTP_PATH_STR_SIZE, ' ');
            // set actual size (excluding space character)
            requestLineBuffer.resize(size - 1);

            requestLineBuffer.shrink();

            connection.skip('\n', MAX_HTTP_VERSION_STR_SIZE);
        }

        return StringView(requestLineBuffer.buff(), requestLineBuffer.size());
    }

    const StringView& Request::getParameter(std::vector<StringView>::size_type index) const {
        return pathParams.at(index);
    }

    const std::vector<StringView>& Request::getParameters() const {
        return pathParams;
    }

    std::vector<StringView>::size_type Request::addParameter(StringView value) {
        pathParams.push_back(value);
        return pathParams.size() - 1;
    }

    std::vector<StringView>::size_type Request::addParameter(const char* ptr, size_t size) {
        return addParameter(StringView(ptr, size));
    }

}
