#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
    #define WIN_PLAT
    #if defined(_WIN64) || defined(__LP64__)
        #define WIN64_PLAT
        #define CYGWIN64_PLAT
    #else
        #define WIN32_PLAT
        #define CYGWIN32_PLAT
    #endif
#endif

#if defined(__unix__) || defined(__unix) || defined(unix)
    #define UNIX_PLAT
    #if defined(__linux__) || defined(__linux) || defined(linux)
        #define LINUX_PLAT
        #if defined(__LP64__) || defined(_LP64) || defined(__x86_64__) || defined(__amd64__)
            #define LINUX64_PLAT
        #else
            #define LINUX32_PLAT
        #endif
    #endif
#endif