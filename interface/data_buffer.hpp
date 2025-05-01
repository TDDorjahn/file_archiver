/**
 * @file data_buffer.hpp
 * @author Tucker Dorjahn
 * @brief Provides an interface to a data buffer, which is a volatile buffer that stores required data for the headers of the files / directories archived.
 * @version 0.1
 * @date 2025-04-29
 * 
 * @details A data buffer stores the required metadata for each file entry in an archive in memory formatted for the archiver to read. If there is only one file
 * to archive, the archiver will independently format and fill the required metadata for the header. Else, the next file will have it's metadata put into the buffer
 * for future jobs. Once it is read, it will have its data erased, then working on getting the metadata for the next archiving job.
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "def.hpp"
#include <array>

using std::array;

class data_buffer {

public:

    data_buffer() = default;
    data_buffer(array<archive_header, buffer_size> buffer);

    

private:

    array<archive_header, buffer_size> buffer;

};