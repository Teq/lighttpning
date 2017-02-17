cmake_minimum_required(VERSION 3.5)

project(lighttpning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIGHTTPNING_SOURCES
    src/exceptions/runtime_error.cpp
    src/exceptions/runtime_error.h
    src/http/connection.h
    src/http/request.cpp
    src/http/request.h
    src/http/response.cpp
    src/http/response.h
    src/http/stream_connection.cpp
    src/http/stream_connection.h
    src/middleware/middleware_chain.cpp
    src/middleware/middleware_chain.h
    src/middleware/middleware_function.h
    src/middleware/middleware.cpp
    src/middleware/middleware.h
    src/middleware/route.cpp
    src/middleware/route.h
    src/middleware/router.cpp
    src/middleware/router.h
    src/misc/putchar_adapter.cpp
    src/misc/putchar_adapter.h
    src/misc/string_buffer.cpp
    src/misc/string_buffer.h
    src/misc/string_view.cpp
    src/misc/string_view.h
    src/request_handler.cpp
    src/request_handler.h
)

set(LIGHTTPNING_TESTS
    test/main.cpp
    test/string_buffer.cpp
    test/middleware.cpp
)

include_directories(
    src/
)

add_library(liblighttpning ${LIGHTTPNING_SOURCES})

add_executable(lighttpning samples/main.cpp)
target_link_libraries (lighttpning liblighttpning)

add_executable(lighttpning_test ${LIGHTTPNING_TESTS})
target_link_libraries (lighttpning_test liblighttpning)

