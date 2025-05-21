add_library(file_archiver_src STATIC common.cpp file.cpp print_common.cpp file_stream.cpp)

target_link_libraries(file_archiver_src PRIVATE file_archiver_interface)
target_include_directories(file_archiver_src PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../interface)