#pragma once
#include <limits.h>
#include <sys/types.h>

constexpr off_t STRLEN_BOUND = ((sizeof(off_t) * CHAR_BIT) * 146 / 485 + 1); 
constexpr off_t STRSIZE_BOUND = STRLEN_BOUND + 1;
constexpr size_t BLOCKSIZE = 512;

constexpr size_t SPARSES_IN_EXTRA_HEADER = 16;
constexpr size_t SPARSES_IN_SPARSE_HEADER = 21;