add_library(file_archiver_common INTERFACE)

target_include_directories(file_archiver_common INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(file_archiver_common INTERFACE common.hpp def_common.hpp print_common.hpp)