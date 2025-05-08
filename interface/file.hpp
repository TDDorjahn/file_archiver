#pragma once

#include <string>
#include <vector>
#include <format>
#include <iostream>

#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include <grp.h>

#include "common.hpp"
#include "print_common.hpp"

struct file_attributes {

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
    std::string link_name;
    magic_t magic;
    version_t version;
    name_t uname;
    name_t gname;
    dev_t major;
    dev_t minor;
    std::string prefix;

    void from_stat(const std::string& file_name, struct stat& st) {

        if(stat(file_name.c_str(), &st) == -1) {

            perror("stat");
            return;

        }

        this->file_name = file_name;
        size = st.st_size;
        mode = st.st_mode;
        uid = st.st_uid;
        gid = st.st_gid;
        mtime = st.st_mtim;
        atime = st.st_atim;
        ctime = st.st_ctim;

        struct passwd* owner_info = getpwuid(uid);
        struct group* group_info = getgrgid(gid);

        if(owner_info == NULL) {

            perror("getpwuid");
            return;

        }

        if(group_info == NULL) {

            perror("getgrgrid");
            return;

        }

        if(S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) {

            major = major(st.st_dev);
            minor = minor(st.st_dev);

        }
        
    }

    void print_attributes() {

        size_t term_width = get_terminal_width();

        std::cout << std::format(
            "\n{:-^20}\n", file_name
        );

    }

};

struct file_entry {

    struct file_attributes header;
    std::vector<char> data;

};