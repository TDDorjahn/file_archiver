cmake_minimum_required(VERSION 3.20)
project(file_archiver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE debug)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

set(CMAKE_IGNORE_PATH "./build")
add_subdirectory(interface/common)
add_subdirectory(interface)
add_subdirectory(src)

add_executable(file_archiver main.cpp)

target_link_libraries(file_archiver PRIVATE file_archiver_interface file_archiver_src)