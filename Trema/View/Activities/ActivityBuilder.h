//
// Created by JajaFil on 5/22/2022.
//

#ifndef TREMA_PROJECT_ACTIVITYBUILDER_H
#define TREMA_PROJECT_ACTIVITYBUILDER_H

#include <memory>
#include "Intent.h"
#include "NoActivityBuilderException.h"

namespace Trema::View
{
    class Window;
    class Activity;
    template<class T, class = std::enable_if_t<std::is_base_of_v<Activity, T>>>
    struct ActivityBuilder
    {
        static std::unique_ptr<T> CreateActivity(Intent intent, std::shared_ptr<Window> window, uint16_t requestCode = -1)
        {
            throw NoActivityBuilderException("You must implement a specialized ActivityBuilder.");
            /* static_assert(!std::is_same<T, Activity>::value);
            return std::move(std::make_unique<T>(std::move(intent), std::move(window), requestCode)); */
        }
    };
}

#endif //TREMA_PROJECT_ACTIVITYBUILDER_H
