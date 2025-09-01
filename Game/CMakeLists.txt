cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(Runner)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
if(LINUX AND APPLE)
  set(RAYLIB_VERSION 5.5)
  find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
  if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
      raylib
      DOWNLOAD_EXTRACT_TIMESTAMP OFF
      URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
      set(FETCHCONTENT_QUIET NO)
      FetchContent_MakeAvailable(raylib)
    endif()
  endif()
endif()
if(WIN32)
  add_subdirectory(C:/raylib/raylib binary_dir)
endif()

# Our Project
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB SOURCES "./*.cpp" "src/*.cpp" "src/**/*.cpp")

#Dependencies
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Signal)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../Network/include)
add_subdirectory(${CMAKE_SOURCE_DIR}/../Network binary_dir2)


add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/"
)

target_link_libraries(${PROJECT_NAME} netLib)

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)



# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()

