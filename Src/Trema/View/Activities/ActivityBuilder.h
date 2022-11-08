//
// Created by JajaFil on 5/22/2022.
//

#ifndef TREMA_PROJECT_ACTIVITYBUILDER_H
#define TREMA_PROJECT_ACTIVITYBUILDER_H

#include <memory>
#include "Intent.h"
#include "ActivityAsBase.h"

namespace Trema::View
{
    class Window;
    class Activity;
    template<class T> requires ActivityAsBase<T>
    struct ActivityBuilder
    {
        std::unique_ptr<T> CreateActivity(Intent intent, uint16_t requestCode = -1)
        {
            return std::move(std::make_unique<T>(std::move(intent), requestCode));
        }
    };
}

#endif //TREMA_PROJECT_ACTIVITYBUILDER_H
