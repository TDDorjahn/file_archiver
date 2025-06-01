#pragma once

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstdint>

/* If you're including any user files for the project here, you're using common wrong. */

/* file.hpp module */

using chksum_t = uint32_t;
using flag_t = char;
using magic_t = char *;
using version_t = char [2];
using name_t = char *;

/* mode flags */
static constexpr int TSUID     = 04000; /* Set user ID on execution. */
static constexpr int TSGID     = 02000; /* Set group ID on execution. */
static constexpr int TSVTX     = 01000; /* reserved. */

static constexpr int TUREAD    = 00400; /* Read by owner. */
static constexpr int TUWRITE   = 00200; /* Write by owner. */
static constexpr int TUEXEC    = 00100; /* Execute or search by owner. */

static constexpr int TGREAD    = 00040; /* Read by group. */
static constexpr int TGWRITE   = 00020; /* Write by group. */
static constexpr int TGEXEC    = 00010; /* Execute or search by group. */

static constexpr int TOREAD    = 00004; /* Read by others. */
static constexpr int TOWRITE   = 00002; /* Write by others. */
static constexpr int TOEXEC    = 00001; /* Execute or search by others. */

/* mode file mask */
static constexpr unsigned int FA_MASK = 0170000;

/* mode file types */
static constexpr unsigned int FA_IFDIR = 0040000;
static constexpr unsigned int FA_IFCHR = 0020000;
static constexpr unsigned int FA_IFBLK = 0060000;
static constexpr unsigned int FA_IFREG = 0100000;
static constexpr unsigned int FA_IFIFO = 0010000;
static constexpr unsigned int FA_IFLNK = 0120000;
static constexpr unsigned int FA_IFSOCK = 0140000;

/* mode file type tests */

bool FA_ISTYPE(mode_t mode, unsigned int mask);
bool FA_ISDIR(mode_t mode);
bool FA_ISCHR(mode_t mode);
bool FA_ISBLK(mode_t mode);
bool FA_ISREG(mode_t mode);
bool FA_ISFIFO(mode_t mode);
bool FA_ISLNK(mode_t mode);
bool FA_ISSOCK(mode_t mode);

/* typeflag flags */
static constexpr char REGTYPE = '0'; /* Regular file. */
static constexpr char AREGTYPE = '\0'; /* Regular file. */
static constexpr char LNKTYPE = '1'; /* Link. */
static constexpr char SYMTYPE = '2'; /* Reserved. */
static constexpr char CHRTYPE = '3'; /* Character special. */
static constexpr char BLKTYPE = '4'; /* Block special. */
static constexpr char DIRTYPE = '5'; /* Directory. In this case, the size field has no meaning. */
static constexpr char FIFOTYPE = '6'; /* FIFO special. Archiving a FIFO file archives its existence, not contents. */
static constexpr char CONTTYPE = '7'; /* Reserved. */

/**
 * @brief Field Descriptions
 * @name file_name
 * @details The file's path name is created using this field, or by using this field in connection with the prefix field. 
 * If the prefix field is included, the name of the file is prefix/name. 
 * This field is null-terminated unless every character is non-null.
 * 
 * @name size
 * @details Value is 0 when the typeflag field is set to LNKTYPE. This field is terminated with a space only.
 * 
 * @name mode
 * @details Provides 9 bits for file permissions and 3 bits for SUID, SGID, and SVTX modes. All values for this field are in octal.
 * During a read operation, the designated mode bits are ignored if the user does not have equal (or higher) permissions or if the modes are not supported.
 * Numeric fields are terminated with a space and a null byte. See common.hpp:file.hpp module:mode flags for details.
 * 
 * @name uid
 * @details Extracted from the corresponding archive fields unless a user with appropriate privileges restores the file.
 * In that case, the field value is extracted from the password and group files instead.
 * Numeric fields are terminated with a space and a null byte.
 * 
 * @name gid
 * @details Extracted from the corresponding archive fields unless a user with appropriate privileges restores the file.
 * In that case, the field value is extracted from the password and group files instead.
 * Numeric fields are terminated with a space and a null byte.
 * 
 * @name mtime
 * @details Value is obtained from the modification-time field of the stat subroutine. This field is terminated with a space only.
 * 
 * @name atime
 * @details Value is obtained from the access-time field of the stat subroutine. This field is terminated with a space only.
 * 
 * @name ctime
 * @details Value is obtained from the change-time field of the stat subroutine. This field is terminated with a space only.
 * 
 * @name chksum
 * @details On calculation, the sum of all bytes in the header structure are treated as spaces.
 * Each unsigned byte is added to an unsigned integer (initialized to 0) with at least 17-bits precision.
 * Numeric fields are terminated with a space and a null byte.
 * 
 * @name flag
 * @details Describes the type of file and subsequently how to handle them. 9 types are given (see common.hpp:file module:typeflag flags)
 * 
 * @name link_name
 * @details Does not use the prefix field to produce a path name.
 * If the path name or linkname value is too long, an error message is returned and any action on that file or directory is canceled.
 * This field is null-terminated unless every character is non-null.
 * 
 * @name magic
 * @details Contains the TMAGIC value, reflecting the extended tar archive format.
 * In this case, the uname and gname fields will contain the ASCII representation for the file owner and the file group.
 * If a file is restored by a user with the appropriate privileges, the uid and gid fields are extracted from the password and group files
 * (instead of the corresponding archive fields).
 * This field is null-terminated.
 * 
 * @name version
 * @details Represents the version of the tar command used to archive the file. This field is terminated with a space only.
 * 
 * @name uname
 * @details Contains the ASCII representation of the file owner. This field is null-terminated.
 * 
 * @name gname
 * @details Contains the ASCII representation of the file group. This field is null-terminated.
 * 
 * @name devmajor
 * @details Contains the device major number. Terminated with a space and a null byte.
 * 
 * @name devminor
 * @details Contains the device minor number. Terminated with a space and a null byte.
 * 
 * @name prefix
 * @details If this field is non-null, the file's path name is created using the prefix/name values together. Null-terminated unless every character is non-null.
 */

/* end file.hpp module */

unsigned int sum_str(char * s);