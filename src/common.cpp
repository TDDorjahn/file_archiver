#include "common.hpp"

/* Definitions for common.hpp functions. */

/* mode file type tests */

bool FA_ISTYPE(mode_t mode, unsigned int mask) { return (mode & FA_MASK) == mask; }
bool FA_ISDIR(mode_t mode) { return FA_ISTYPE(mode, FA_IFDIR); }
bool FA_ISCHR(mode_t mode) { return FA_ISTYPE(mode, FA_IFCHR); }
bool FA_ISBLK(mode_t mode) { return FA_ISTYPE(mode, FA_IFBLK); }
bool FA_ISREG(mode_t mode) { return FA_ISTYPE(mode, FA_IFREG); }
bool FA_ISFIFO(mode_t mode) { return FA_ISTYPE(mode, FA_IFIFO); }
bool FA_ISLNK(mode_t mode) { return FA_ISTYPE(mode, FA_IFLNK); }
bool FA_ISSOCK(mode_t mode) { return FA_ISTYPE(mode, FA_IFSOCK); }

unsigned int sum_str(char * s) {

    char * t;
    unsigned sum = 0;

    for(t = s; *t != '\0'; t++) 
    {

        sum += (unsigned)*t;

    }

    return sum;

}