#include "print_common.hpp"

size_t get_terminal_width() {

#ifdef LINUX_PLAT

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;

#else

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.srWindow.Right - csbi.srWindow.left + 1;

#endif

}

#ifdef LINUX_PLAT

auto timespec_to_timepoint(timespec& ts) -> std::chrono::system_clock::time_point {

    return std::chrono::system_clock::from_time_t(ts.tv_sec) + std::chrono::nanoseconds(ts.tv_nsec);

}

char file_type(mode_t mode)
{

    if (FA_ISDIR(mode))
        return 'd';
    else if (FA_ISCHR(mode))
        return 'c';
    else if (FA_ISBLK(mode))
        return 'b';
    else if (FA_ISREG(mode))
        return '-';
    else if (FA_ISFIFO(mode))
        return 'p';
    else if (FA_ISLNK(mode))
        return 'l';
    else
        return 's';
}

std::string mode_to_str(mode_t mode) 
{

    std::string mode_str(10, '-');
    mode_str[0] = file_type(mode);
    mode_str[1] = (mode & S_IRUSR) ? 'r' : '-';
    mode_str[2] = (mode & S_IWUSR) ? 'w' : '-';
    mode_str[3] = (mode & S_IXUSR) ? 'x' : '-';
    mode_str[4] = (mode & S_IRGRP) ? 'r' : '-';
    mode_str[5] = (mode & S_IWGRP) ? 'w' : '-';
    mode_str[6] = (mode & S_IXGRP) ? 'x' : '-';
    mode_str[7] = (mode & S_IROTH) ? 'r' : '-';
    mode_str[8] = (mode & S_IWOTH) ? 'w' : '-';
    mode_str[9] = (mode & S_IXOTH) ? 'x' : '-';
    return mode_str;
    
}

#endif