cmake_minimum_required(VERSION 3.10)
project(networking VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB NETLIB_SOURCES "src/*.cpp")
add_library(NetLib STATIC ${NETLIB_SOURCES})


target_include_directories(NetLib PUBLIC include)


if(WIN32)
    target_link_libraries(networking ws2_32)
endif()
