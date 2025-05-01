#include <sys/types.h>
#include <string>

template<size_t size>
class fixed_string {

public:

    fixed_string() = default;
    fixed_string(size_t size, const char * str);
    fixed_string(std::string str);
    fixed_string(const fixed_string& other);
    fixed_string(fixed_string&& other);


private:

    char m_buffer[size];
    size_t m_size;

};