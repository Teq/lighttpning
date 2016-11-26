cmake_minimum_required(VERSION 3.6)
project(lighttpning)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp httpcontext.h lighttpning.h middleware.h)
add_executable(lighttpning ${SOURCE_FILES})
