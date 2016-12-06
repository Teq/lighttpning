cmake_minimum_required(VERSION 3.5)

project(lighttpning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIGHTTPNING_SRC
    src/http/connection.h
    src/http/request.cpp
    src/http/request.h
    src/http/response.cpp
    src/http/response.h
    src/http/stream_connection.cpp
    src/http/stream_connection.h
    src/application.cpp
    src/application.h
    src/middleware/middleware.h
    src/middleware/middleware_chain.cpp
    src/middleware/middleware_chain.h
    src/middleware/middleware_node.cpp
    src/middleware/middleware_node.h
    src/middleware/router.cpp
    src/middleware/router.h
)

set(SOURCE_FILES main.cpp ${LIGHTTPNING_SRC})

add_executable(lighttpning ${SOURCE_FILES})
