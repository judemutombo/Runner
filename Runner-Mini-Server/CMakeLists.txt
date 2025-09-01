cmake_minimum_required(VERSION 3.10)
project(miniserver VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "./*.cpp" "src/*.cpp" "src/**/*.cpp")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Network/include)
file(GLOB NET_SOURCES  "./../Network/src/*.cpp" )

file(GLOB NLOHMANN "externals/nlohmann" )
include_directories(${NLOHMANN}) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Signal/include)



add_executable(miniserver ${SOURCES} ${NET_SOURCES})

set_target_properties(miniserver PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)
if(UNIX)
    target_link_libraries(miniserver PUBLIC pthread)
endif()

if(WIN32)
    target_link_libraries(miniserver ws2_32)
endif()