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
    *version = {0};
    prefix = "";

}

file_attributes::file_attributes(std::string file_name)
{

    struct stat st;
    from_stat(file_name, st);

}

file_attributes::file_attributes(const file_attributes &fa)
{

    file_name = fa.file_name;
    size = fa.size;
    mode = fa.mode;
    uid = fa.uid;
    gid = fa.gid;
    mtime = fa.mtime;
    atime = fa.atime;
    ctime = fa.ctime;
    chksum = fa.chksum;
    flag = fa.flag;
    link_name = fa.link_name;
    magic = fa.magic;
    std::copy(fa.version, fa.version + 1, version);
    uname = fa.uname;
    gname = fa.gname;
    dev_major = fa.dev_major;
    dev_minor = fa.dev_minor;
    prefix = fa.prefix;


}

file_attributes::file_attributes(file_attributes &&fa) noexcept :
    file_name(std::move(fa.file_name)),
    size(std::exchange(fa.size, 0)),
    mode(std::exchange(fa.mode, 0)),
    uid(std::exchange(fa.uid, 0)),
    gid(std::exchange(fa.gid, 0)),
    mtime(fa.mtime),
    atime(fa.atime),
    ctime(fa.ctime),
    chksum(std::exchange(fa.chksum, 0)),
    flag(std::exchange(fa.flag, '\0')),
    link_name(std::exchange(fa.link_name, nullptr)),
    magic(std::exchange(fa.magic, nullptr)),
    version{fa.version[0], fa.version[1]},
    uname(std::exchange(fa.uname, nullptr)),
    gname(std::exchange(fa.gname, nullptr)),
    dev_major(std::exchange(fa.dev_major, 0)),
    dev_minor(std::exchange(fa.dev_minor, 0)),
    prefix(std::move(fa.prefix))
{

    fa.atime = {};
    fa.mtime = {};
    fa.ctime = {};

}

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

    if (flag == LNKTYPE || flag == SYMTYPE)
    {

        ssize_t link_str_len;

        if ((link_str_len = readlink(file_name.c_str(), link_name, sizeof(link_name))) == -1)
        {

            perror("readlink.\n");
        }
        else
        {

            link_name[link_str_len] = '\0';
        }

    } else {

        link_name = (char *)"\0";

    }

    magic = (char *)"FA\0";
    version[0] = '1'; version[1] = '\0';

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

    calculate_checksum();

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

chksum_t file_attributes::calculate_checksum()
{

    uint32_t sum = 0;

    auto process_field = [&sum](const auto& field) {

        const uint32_t* bytes = reinterpret_cast<const uint32_t*>(&field);
        for(size_t i = 0; i < sizeof(field); i++) {

            sum ^= (bytes[i]) << (8 * (i % 4));

        }

        std::cout << "Size of field: " << sizeof(field) << '\n';

    };

    process_field(file_name.data());
    process_field(size);
    process_field(mode);
    process_field(uid);
    process_field(gid);
    process_field(mtime);
    process_field(atime);
    process_field(ctime);
    process_field(flag);
    process_field(link_name);
    process_field(magic);
    process_field(version);
    process_field(uname);
    process_field(gname);
    process_field(dev_major);
    process_field(dev_minor);
    process_field(prefix.data());

    return sum;
    
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