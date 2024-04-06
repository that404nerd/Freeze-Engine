#pragma once

#include <spdlog/spdlog.h>

#include <string>

#include <box2d/b2_math.h>

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
        #define FZ_ASSERT(x, ...) {FZ_ERROR(x, ##__VA_ARGS__); raise(SIGTRAP);}
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

   inline float MetersPerPixelFactor = 32.0f;

   inline float PixelToMeter(const float value) { return (value * (1.0f / MetersPerPixelFactor)); }
   inline b2Vec2 PixelToMeter(const b2Vec2& vector) { return b2Vec2(PixelToMeter(vector.x), PixelToMeter(vector.y)); }

   inline float MeterToPixel(const float value) { return (value * MetersPerPixelFactor); }
   inline b2Vec2 MeterToPixel(const b2Vec2& vector) { return b2Vec2(MeterToPixel(vector.x), MeterToPixel(vector.y)); }

};
