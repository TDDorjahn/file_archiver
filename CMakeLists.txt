cmake_minimum_required(VERSION 3.20)
project(file_archiver)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_IGNORE_PATH "./build")
set(HOME_DIR ${CMAKE_SOURCE_DIR})
set(SRC_DIR ${HOME_DIR}/src)
set(HEADER_DIR ${HOME_DIR}/interface)

file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADERS ${HEADER_DIR}/*.hpp)

add_library(fa_lib ${SRCS})

add_executable(file_archiver main.cpp)
target_link_libraries(file_archiver PRIVATE fa_lib)