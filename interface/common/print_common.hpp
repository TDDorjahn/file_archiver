/**
 * @file print_common.hpp
 * @author Tucker Dorjahn
 * @brief Provides a template for common printing procedures with different objects.
 * @todo Move all common print jobs from structs / classes into print_common.hpp
 * @version 0.1
 * @date 2025-05-08
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#pragma once

#include "def_common.hpp"
#include "common.hpp"

#ifdef LINUX_PLAT
#include <sys/ioctl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <Windows.h>
#endif

#include <chrono>
#include <string>

size_t get_terminal_width();
auto timespec_to_timepoint(timespec& ts) -> std::chrono::system_clock::time_point;
char file_type(mode_t mode);
std::string mode_to_str(mode_t mode);