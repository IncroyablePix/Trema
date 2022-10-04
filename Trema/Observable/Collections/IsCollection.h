//
// Created by Benjam on 10/3/2022.
//

#ifndef TREMA_PROJECT_ISCOLLECTION_H
#define TREMA_PROJECT_ISCOLLECTION_H

#include <memory>

namespace Trema::Observable
{
    template<typename T>
    concept IsCollection = requires(T t)
    {
        typename T::iterator;
        typename T::const_iterator;
        { t.begin() } -> std::same_as<typename T::iterator>;
        { t.end() } -> std::same_as<typename T::iterator>;
        { t.begin() } -> std::same_as<typename T::const_iterator>;
        { t.end() } -> std::same_as<typename T::const_iterator>;
    };
}

#endif //TREMA_PROJECT_ISCOLLECTION_H
