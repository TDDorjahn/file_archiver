/**
 * @file data_buffer.hpp
 * @author Tucker Dorjahn
 * @brief Provides an interface to a data buffer, which is a volatile buffer that stores required data for the headers of the files / directories archived.
 * @version 0.1
 * @date 2025-04-29
 * 
 * @details A data buffer stores the required metadata for each file entry in an archive in memory formatted for the archiver to read. If there is only one file
 * to archive, the archiver will independently format and fill the required metadata for the header. Else, the next file will have it's metadata put into the buffer
 * for future jobs. Once it is read, it will have its data erased, then working on getting the metadata for the next archiving job.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "structdef.hpp"
#include "sparse.hpp"
#include <array>

using std::array;

template <size_t N>
class data_buffer {

public:

    using storage_type = array<archive_header, N>;

    using value_type = archive_header;
    using pointer = value_type*;
    using const_pointer = const value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    

    data_buffer() = default;
    data_buffer(array<archive_header, N> buffer);

private:

    array<archive_header, N> buffer;

    const char * _get_filename(char (&_name)[100]);
    const char * _get_mode(char (&_mode)[8]);
    const char * _get_uid(char (&_uid)[8]);
    const char * _get_gid(char (&_gid)[8]);
    const char * _get_file_size(char (&_size)[12]);
    const char * _get_mtime(char (&_mtime)[12]);
    const char * _calc_chksum(char (&_checksum)[8]);
    const char * _get_file_type(char flagtype);
    const char * _get_linkname(char (&_linkname)[100]);
    const char * _get_magic_num(char (&_magic)[6]);
    const char * _get_verison(char (&_version)[2]);
    const char * _get_uname(char (&_uname)[32]);
    const char * _get_gname(char (&_gname)[32]);
    const char * _get_devmajor(char (&_devmajor)[8]);
    const char * _get_devminor(char (&_devminor)[8]);
    const char * _pad_extra(char (&_extra)[155]);

};

/*
struct archive_header {

    char name[100];
    char mode[8];
    char uid[8];
    char gid[8];
    char size[12];
    char mtime[12];
    char checksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char extra[155];

};
*/