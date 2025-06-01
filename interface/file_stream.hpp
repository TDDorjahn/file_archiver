#pragma once

#include <array>
#include <iterator>
#include <fstream>
#include <string>

static constexpr unsigned FILE_STREAM_MAX_SIZE = 512;
static constexpr unsigned FILE_STREAM_MAX_LEN = FILE_STREAM_MAX_SIZE - 1;

/**
 * @brief A stream of 512 bytes containing data of file contents.
 * @details The class file_stream shall contain an array whose modifiers
 *          and accessors will only work from the left-most non-empty value.
 *          The stream is flushed and redirected into an archive file entry
 *          once it is full.  The process will repeat until a file entry is successfully
 *          entered into the archive (in which case, the stream might not be completely filled).
 */
class file_stream {

public:
    
    /* No reverse iterators needed for unidirectional container. */

    using value_type = char;
    using pointer = char *;
    using reference = char &;
    using const_pointer = const char *;
    using const_reference = const char &;
    using iterator = char *;
    using const_interator = const char *;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    /* ctors */
    file_stream() noexcept;
    file_stream(value_type (&stream)[512]) noexcept;
    file_stream(value_type stream[512]) noexcept;
    file_stream(std::array<value_type, 512> stream) noexcept;
    file_stream(std::array<value_type, 512>& stream) noexcept;
    file_stream(const file_stream& fs) noexcept;
    file_stream(file_stream&& fs) noexcept;

    /* Modifiers */
    constexpr void put(value_type byte) noexcept;
    constexpr void clear() noexcept;
    constexpr void extract(std::ofstream& out_file, std::string& file_name) noexcept;

    
    /* Accessors */
    constexpr reference get() noexcept;
    constexpr const_reference peak() const noexcept;

    constexpr reference front() noexcept;
    constexpr const_reference front() const noexcept;

    constexpr reference back() noexcept;
    constexpr const_reference back() const noexcept;

    constexpr pointer data() noexcept;
    constexpr const_pointer data() const noexcept;


private:

    std::array<value_type, 512> stream; //holds file data.
    bool full; // flag for full array and subsequent flush.
    difference_type buf_ptr; // buffer iterator

};

std::ostream& operator<<(std::ostream& os, const file_stream& obj);