cmake_minimum_required(VERSION 3.5)

project(lighttpning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(LIGHTTPNING_SRC
    src/application.cpp
    src/http/stream_connection.cpp
    src/http/request.cpp
    src/http/response.cpp
)

set(SOURCE_FILES main.cpp ${LIGHTTPNING_SRC})

add_executable(lighttpning ${SOURCE_FILES})
