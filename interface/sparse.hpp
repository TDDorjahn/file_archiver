#include <sys/types.h>
#include <limits.h>

struct sparse {

    char offset[12];
    char total_bytes[12];

} typedef sparse;

struct sparse_header {



} typedef sparse_header;

struct sparse_array {

    off_t pos;
    off_t total_bytes;

} typedef sparse_array;

struct prog_info {

    char * program_name;
    int verbose;

} typedef prog_info;

struct buffer {

    static char * buf;
    static size_t size;

} typedef buffer;


struct sparse_map {

    sparse_array * sparse_map;
    size_t map_size;

} typedef sparse_map;