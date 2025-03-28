cmake_minimum_required(VERSION 3.10)
project(miniserver VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "./*.cpp" "src/*.cpp" "src/**/*.cpp")

include_directories(C:/Users/MATHUSALEM/Documents/C++/Runner/Network/include)
file(GLOB NET_SOURCES  "C:/Users/MATHUSALEM/Documents/C++/Runner/Network/src/*.cpp" )

file(GLOB NLOHMANN "externals/nlohmann" )
include_directories(${NLOHMANN}) 


add_executable(miniserver ${SOURCES} ${NET_SOURCES})

if(WIN32)
    target_link_libraries(miniserver ws2_32)
endif()