#pragma once

#include <string>
#include <array>
#include <format>
#include <iostream>
#include <utility>
#include <algorithm>

#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>

#include "print_common.hpp"
#include "file_stream.hpp"

static constexpr const char * EOA = "__EOA  ";
static constexpr const char * FAMAGIC = "fafmt"; //Only supporting our own format at the moment
static constexpr unsigned int FAMAGIC_LEN = 6;
consteval size_t MAGIC_LEN(magic_t magic);

class file_attributes {

private:
    std::string file_name;
    size_t size;
    mode_t mode;
    uid_t uid;
    gid_t gid;
    struct timespec mtime;
    struct timespec atime;
    struct timespec ctime;
    chksum_t chksum;
    flag_t flag;
    char * link_name;
    magic_t magic;
    version_t version;
    name_t uname;
    name_t gname;
    unsigned dev_major;
    unsigned dev_minor;
    std::string prefix;

public:

    file_attributes();
    file_attributes(std::string file_name);
    file_attributes(const file_attributes& fa);
    file_attributes(file_attributes&& fa) noexcept;

    void from_stat(const std::string& file_name, struct stat& st);
    void print_attributes();

private:
    void _get_flag_type(flag_t& flag, mode_t mode);
    chksum_t calculate_checksum();

};

class end_of_archive {

public:
    end_of_archive();

private:
    std::array<char, 512> eoa_flag;
    void _fill_eoa_flag();

};

struct file_entry {

    file_attributes header;
    file_stream stream;

};