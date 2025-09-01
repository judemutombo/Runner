cmake_minimum_required(VERSION 3.10)
project(netLib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB NETLIB_SOURCES "./*.cpp" "src/*.cpp")
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Signal)
add_library(netLib STATIC ${NETLIB_SOURCES})



if(WIN32)
    target_link_libraries(netLib ws2_32)
endif()
