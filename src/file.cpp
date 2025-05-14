#include "file.hpp"

consteval size_t MAGIC_LEN(magic_t magic) {

    return (sizeof(magic)/sizeof(magic[0]));

}

file_attributes::file_attributes() {

    file_name = "";
    size = 0;
    mode = 00;
    uid = 0;
    gid = 0;
    mtime = {(long int)0, (long int)0};
    atime = {(long int)0, (long int)0};
    ctime = {(long int)0, (long int)0};
    chksum = 0;
    flag = 0;
    link_name = "";
    magic = (char *)"";
    *version = {0};
    prefix = "";

}

file_attributes::file_attributes(std::string file_name)
{

    struct stat st;
    from_stat(file_name, st);

}

//file_attributes::file_attributes(const file_attributes &fa) : file_attributes{ fa }
//{}

file_attributes::file_attributes(file_attributes &&fa) noexcept :
    file_name(std::move(fa.file_name)),
    size(std::move(fa.size)),
    mode(std::move(fa.mode)),
    uid(std::move(fa.uid)),
    gid(std::move(fa.gid)),
    mtime(std::move(fa.mtime)),
    atime(std::move(fa.atime)),
    ctime(std::move(fa.ctime)),
    chksum(std::move(fa.chksum)),
    flag(std::move(fa.flag)),
    link_name(std::move(fa.link_name)),
    magic(std::move(fa.magic)),
    version(std::move(*fa.version)),
    uname(std::move(fa.uname)),
    gname(std::move(fa.gname)),
    dev_major(std::move(fa.dev_major)),
    dev_minor(std::move(fa.dev_minor)),
    prefix(std::move(fa.prefix))
{}

void file_attributes::from_stat(const std::string &file_name, struct stat &st)
{

    if (stat(file_name.c_str(), &st) == -1)
    {

        perror("stat");
        return;
    }

    this->file_name = file_name;

    size_t prefix_count = std::count(file_name.begin(), file_name.end(), '/');

    if(prefix_count <= 1)
        prefix = "./";
    else 
    {

        size_t last_slash = file_name.rfind('/');
        prefix = std::string(file_name, 0, last_slash + 1);
        this->file_name.erase(0, last_slash + 1);

    }

    size = st.st_size;
    mode = st.st_mode;
    uid = st.st_uid;
    gid = st.st_gid;
    mtime = st.st_mtim;
    atime = st.st_atim;
    ctime = st.st_ctim;
    _get_flag_type(flag, mode); //init flag
    

    struct passwd *owner_info = getpwuid(uid);
    struct group *group_info = getgrgid(gid);

    if (owner_info == NULL)
    {

        perror("getpwuid");
        return;
    }

    if (group_info == NULL)
    {

        perror("getgrgrid");
        return;
    }

    uname = owner_info->pw_name;
    gname = group_info->gr_name;

    dev_major = major(st.st_dev);
    dev_minor = minor(st.st_dev);

}

void file_attributes::print_attributes()
{

    std::cout << std::format(
        "File: {}\tSize: {}\tPermissions: ({:#o}/{})\tDirectory: {}\n\
UID: ({}, {})\tGID: ({}, {})\n\
Device: {}, {}\n\
Access: {}\n\
Modified: {}\n\
Changed: {}\n",
        file_name, size, mode & 07777, mode_to_str(mode), prefix, uid, uname,
        gid, gname, dev_major, dev_minor, timespec_to_timepoint(atime), timespec_to_timepoint(mtime), timespec_to_timepoint(ctime));
}

void file_attributes::_get_flag_type(flag_t& flag, mode_t mode) {

    if(mode) {

        if(FA_ISREG(mode))
            flag = REGTYPE;
        else if(FA_ISLNK(mode))
            flag = LNKTYPE;
        else if(FA_ISCHR(mode))
            flag = CHRTYPE;
        else if(FA_ISBLK(mode))
            flag = BLKTYPE;
        else if(FA_ISDIR(mode))
            flag = DIRTYPE;
        else if(FA_ISFIFO(mode))
            flag = FIFOTYPE;
        else
            flag = AREGTYPE;

        /* TODO: SYMTYPE and CONTTYPE user implementation here. If neither types are true, keep as AREGTYPE. */

        return;
    }

    perror("_get_flag_type(flag_t& flag, mode_t mode): mode uninitialized.\n");

}

unsigned int file_attributes::_do_chksum() {

    /**
     * @brief _do_chksum() field list
     * 
     * std::string file_name
     * unsigned long size
     * unsigned int mode
     * unsigned int uid
     * unsigned int gid
     * struct timespec
     *      mtime
     *      atime
     *      ctime
     *          long tv_sec
     *          long tv_nsec
     * unsigned int chksum
     * char flag
     * std::string link_name
     * char * magic
     * char version[2]
     * char * uname
     * char * gname
     * unsigned int dev_major
     * unsigned int dev_minor
     * std::string prefix
     * 
     */

}

end_of_archive::end_of_archive() { _fill_eoa_flag(); }

/**
 * @brief Fills eoa_flag with '\0', last 7 bytes are "__EOA  ", marking the end of the archive.
 * 
 */
void end_of_archive::_fill_eoa_flag() {

    eoa_flag = { '\0' };
    eoa_flag[505] = '_';
    eoa_flag[506] = '_';
    eoa_flag[507] = 'E';
    eoa_flag[508] = 'O';
    eoa_flag[509] = 'A';
    eoa_flag[510] = ' ';
    eoa_flag[511] = ' ';

}