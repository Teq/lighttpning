cmake_minimum_required(VERSION 3.5)

project(lighttpning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(LIGHTTPNING_SRC
    src/http/connection.h
    src/http/request.cpp
    src/http/request.h
    src/http/response.cpp
    src/http/response.h
    src/http/stream_connection.cpp
    src/http/stream_connection.h
    src/lighttpning.cpp
    src/lighttpning.h
    src/middleware/middleware.cpp
    src/middleware/middleware.h
    src/middleware/middleware_chain.cpp
    src/middleware/middleware_chain.h
    src/middleware/middleware_function.h
    src/middleware/route.cpp
    src/middleware/route.h
    src/middleware/router.cpp
    src/middleware/router.h
    src/misc/string_buffer.cpp
    src/misc/string_buffer.h
    src/misc/string_view.cpp
    src/misc/string_view.h
    src/exceptions/runtime_error.cpp
    src/exceptions/runtime_error.h
    )

set(SOURCE_FILES samples/main.cpp ${LIGHTTPNING_SRC})

add_executable(lighttpning ${SOURCE_FILES})
