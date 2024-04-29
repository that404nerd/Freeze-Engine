#pragma once

#include <spdlog/spdlog.h>

#include <string>

#include "root_dir.h"

#ifdef RELEASE
    #define FZ_INFO(x, ...) spdlog::info()
    #define FZ_WARN(x, ...) spdlog::warn()
    #define FZ_ERROR(x, ...) spdlog::error()

    #ifdef __linux__
        #define FZ_ASSERT(x, ...) {FZ_ERROR(); raise(SIGTRAP);}
    #else
        // For MSVC
        #define FZ_ASSERT(x, ...) {FZ_ERROR(); __debugbreak();}
    #endif

    #define FZ_EXIT() {exit(0);}
#else
    #define FZ_INFO(x, ...) spdlog::info(x, ##__VA_ARGS__)
    #define FZ_WARN(x, ...) spdlog::warn(x, ##__VA_ARGS__)
    #define FZ_ERROR(x, ...) spdlog::error(x, ##__VA_ARGS__)

    #ifdef __linux__
        #include <signal.h>
        #define FZ_ASSERTM(x, ...) {FZ_ERROR(x, ##__VA_ARGS__); raise(SIGTRAP);}
        #define FZ_ASSERT(x) { FZ_ERROR(x); raise(SIGTRAP); }
    #else
        // For MSVC
        #define FZ_ASSERT(x, ...) {FZ_ERROR(x, ##__VA_ARGS__); __debugbreak();}
    #endif

    #define FZ_EXIT() {FZ_INFO("Called Exit Function"); exit(0);}
#endif

namespace Freeze {
    class Utils {
    public:
        Utils() = default;

        static std::string GetFilePath(const std::string& filepath)
        {
            std::string newFilePath = rootDir + filepath;
            return newFilePath;
        }
    };
};
