// ================================================
// File: debug.hpp
// Created on: 2025-06-12 11:36:01
// Last modified: 2025-06-12 11:46:42
// Created by: Alwin R Ajeesh
// ================================================
#pragma once

#include <iostream>
#include <string>
#include <cstring>

namespace debug {

// ANSI color codes
constexpr const char* RESET  = "\033[0m";
constexpr const char* GREEN  = "\033[32m";
constexpr const char* YELLOW = "\033[33m";
constexpr const char* RED    = "\033[31m";
constexpr const char* CYAN   = "\033[36m";

// Extract filename from path
inline const char* extract_filename(const char* path) {
    const char* file = strrchr(path, '/');
    if (!file) file = strrchr(path, '\\');
    return file ? file + 1 : path;
}

// Main log function with color
inline void log(const std::string& message, const char* file, int line, const char* color) {
    std::cerr << color << "[DEBUG] " << extract_filename(file) << ":" << line
              << " - " << message << RESET << std::endl;
}

// Shorthand macros
#define DEBUG_LOG(msg)   ::debug::log(msg, __FILE__, __LINE__, ::debug::CYAN)
#define INFO_LOG(msg)    ::debug::log(msg, __FILE__, __LINE__, ::debug::GREEN)
#define WARN_LOG(msg)    ::debug::log(msg, __FILE__, __LINE__, ::debug::YELLOW)
#define ERROR_LOG(msg)   ::debug::log(msg, __FILE__, __LINE__, ::debug::RED)

} // namespace debug

