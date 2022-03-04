//
// Created by JajaFil on 3/4/2022.
//

#include <algorithm>
#include "FileSplits.h"


namespace Trema::View
{
    std::string GetFilePath(const std::string& path)
    {
        auto pathEnd = path.find_last_of("/\\");
        auto pathName = pathEnd == std::string::npos ? path : path.substr(0, pathEnd);
        return pathName;
    }

    std::string GetFileName(const std::string& path)
    {
        auto fileNameStart = path.find_last_of("/\\");
        auto fileName = fileNameStart == std::string::npos ? path : path.substr(fileNameStart + 1);
        return fileName;
    }

    std::string GetFileExtension(const std::string& path)
    {
        auto fileName = GetFileName(path);
        auto extStart = fileName.find_last_of('.');
        auto ext = extStart == std::string::npos ? "" : fileName.substr(extStart + 1);
        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c)
        {
            return static_cast<unsigned char>(std::tolower(c));
        });
        return ext;
    }

    std::string GetFileWithoutExtension(const std::string& path)
    {
        auto fileName = GetFileName(path);
        auto extStart = fileName.find_last_of('.');
        auto ext = extStart == std::string::npos ? "" : fileName.substr(0, extStart);

        std::transform(ext.begin(), ext.end(), ext.begin(), [](unsigned char c)
        {
            return static_cast<unsigned char>(std::tolower(c));
        });

        return ext;
    }

    std::string ToLowerCase(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c)
        {
            return static_cast<unsigned char>(std::tolower(c));
        });

        return str;
    }

    FileSplit::FileSplit(const std::string &path)
    {
        FileName = GetFileName(path);
        FilePath = GetFilePath(path);
        FileExtension = GetFileExtension(path);
        FileWithoutExtension = GetFileWithoutExtension(path);
        FileWithoutExtensionLowered = ToLowerCase(FileWithoutExtension);
    }
}