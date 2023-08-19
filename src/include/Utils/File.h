#pragma once

#include <fstream>
#include <string>

namespace Casper
{
struct File
{
    /// <summary>
    /// Checks if a file exists and is readable.
    /// </summary>
    inline static bool Exists(const std::string& filePath)
    {
        std::ifstream file(filePath.c_str());
        return file.good();
    }
    /// Overloaded version of Exists that takes a char*
    inline static bool Exists(const char* filePath)
    {
        std::ifstream file(filePath);
        return file.good();
    }
};
} // namespace Casper
