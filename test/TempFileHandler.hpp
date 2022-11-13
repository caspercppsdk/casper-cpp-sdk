#pragma once
#include <filesystem>
#include <string>
#include <iostream>
#include <fstream>

class TempFileHandler
{
public:
    TempFileHandler(const std::string& fileContent, const std::string& fileName)
    {
        m_file = std::filesystem::temp_directory_path().append(fileName).concat(".pem").string();
        std::ofstream file;
        file.open(m_file);
        file << fileContent;
        file.close();
    }

    ~TempFileHandler()
    {
        std::filesystem::remove(m_file);
    }

    const std::string& getPath()
    {
        return m_file;
    }
private:
    std::string m_file;
};