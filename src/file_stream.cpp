#include "file_stream.hpp"

/* ctors */
file_stream::file_stream() noexcept : stream{'\0'}, full(false), buf_ptr(0)
{}

file_stream::file_stream(value_type (&stream)[512]) noexcept : stream{*stream}, buf_ptr(0) {}
file_stream::file_stream(value_type stream[512]) noexcept : stream{*stream}, buf_ptr(0) {}
file_stream::file_stream(std::array<value_type, 512> stream) noexcept : stream{stream}, buf_ptr(0) {}
file_stream::file_stream(std::array<value_type, 512> &stream) noexcept : stream{stream}, buf_ptr(0) {}
file_stream::file_stream(const file_stream &fs) noexcept : stream(fs.stream), full(fs.full), buf_ptr(fs.buf_ptr) {}
file_stream::file_stream(file_stream &&fs) noexcept : stream(fs.stream), full(fs.full), buf_ptr(fs.buf_ptr) {}

/* Modifiers */
constexpr void file_stream::put(value_type byte) noexcept {

    stream[buf_ptr] = byte;
    ++buf_ptr;

    if(buf_ptr == FILE_STREAM_MAX_LEN)
        full = true;

}

constexpr void file_stream::clear() noexcept {

    for(auto& it : stream) {

        it = '\0';

    }

    buf_ptr = 0;
    full = false;
    
}

constexpr void file_stream::extract(std::ofstream& out_file, std::string& file_name) noexcept
{

    if (out_file.is_open())
    {

        out_file.write(stream.data(), stream.size());
        this->clear();

    }
    else 
    {

        out_file.open(file_name, std::ios_base::binary);
        out_file.write(stream.data(), stream.size());
        this->clear();
        
    }

}

/* Accessors */

constexpr file_stream::reference file_stream::get() noexcept
{

    return stream[0];

}

constexpr file_stream::const_reference file_stream::peak() const noexcept
{

    return stream[0];

}

constexpr file_stream::reference file_stream::front() noexcept
{

    return stream[0];

}

constexpr file_stream::const_reference file_stream::front() const noexcept
{

    return stream[0];

}

constexpr file_stream::reference file_stream::back() noexcept
{

    return stream[FILE_STREAM_MAX_LEN];

}

constexpr file_stream::const_reference file_stream::back() const noexcept
{

    return stream[FILE_STREAM_MAX_LEN];

}

constexpr file_stream::pointer file_stream::data() noexcept
{

    return stream.data();

}

constexpr file_stream::const_pointer file_stream::data() const noexcept
{

    return stream.data();

}

std::ostream& operator<<(std::ostream& os, const file_stream& obj)
{

    os << obj.data();
    return os;

}