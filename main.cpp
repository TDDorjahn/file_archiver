#include "file.hpp"

int main(int argc, char* argv[]) {

    if(argc != 2) {

        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return 1;

    }

    const char * filename = argv[1];
    struct stat f_stat;

    struct file_attributes fa;

    std::cout << "Size of (struct file_attributes).uninitialized: " << sizeof(fa) << "B\n";

    fa.from_stat(filename, f_stat);

    std::cout << "Size of (struct file_attributes).initialized: " << sizeof(fa) << "B\n";

    fa.print_attributes();

    return 0;
}