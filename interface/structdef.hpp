#pragma once

/**
 * @file structdef.hpp
 * @author Tucker Dorjahn
 * @brief Provides definitions for structures and their attributes.
 * @version 0.1
 * @date 2025-05-01
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <bits/stat.h>
#include <time.h>
#include <sys/types.h>

#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <string>

#define INCONSTEXPR inline constexpr

namespace fs = std::filesystem;
using path = std::string; using file = std::string;

/* Flags for typeflag */
constexpr char normal_file = '0';
constexpr char hard_link = '1';
constexpr char sym_link = '2';
constexpr char char_type = '3';
constexpr char block_type = '4';
constexpr char directory_type = '5';
constexpr char fifo_type = '6';
constexpr char cont_type = '7';

/* Extenders */
constexpr char extension = 'x'; // Extended header flag that refers to next file in the archive.
constexpr char global_extension = 'g'; //Global header extender.

/* Bits used in mode field (octal values) */
constexpr int set_UID = 04000;
constexpr int set_GID = 02000;
constexpr int owner_read = 00400;
constexpr int owner_write = 00200;
constexpr int owner_exec = 00100;
constexpr int group_read = 00040;
constexpr int group_write = 00020;
constexpr int group_exec = 00010;
constexpr int other_read = 00004;
constexpr int other_write = 00002;
constexpr int other_exec = 00001;

/* Flags for the encoding field */
constexpr char ascii = 'a';
constexpr char utf8 = 'u';

constexpr int HDR_SIZE = 512;

struct archive_header {

    file filename;
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

struct archive_stat_info {

    char * original_file_name;
    char * file_name;
    bool trailing_slash;
    char * link_name;

    char * uname;
    char * gname;
    struct stat stat;

    struct timespec access_time;
    struct timespec modified_time;
    struct timespec change_time;

    off_t archive_file_size;

};

/* Data buffer fields */
constexpr int buffer_size = 5;