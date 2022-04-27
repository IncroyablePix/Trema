//
// Created by JajaFil on 3/4/2022.
//

#ifndef TREMA_FILESPLITS_H
#define TREMA_FILESPLITS_H

#include <string>

namespace Trema::View
{
    struct FileSplit
    {
        explicit FileSplit(const std::string &path);

        std::string FileName;
        std::string FilePath; //
        std::string FileExtension; // Without the dot !
        std::string FileWithoutExtension; // Without the dot !
        std::string FileWithoutExtensionLowered; // Still without the dot
    };
}

#endif //TREMA_FILESPLITS_H
