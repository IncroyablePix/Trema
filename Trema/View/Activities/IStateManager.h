//
// Created by JajaFil on 5/23/2022.
//

#ifndef TREMA_PROJECT_ISTATEMANAGER_H
#define TREMA_PROJECT_ISTATEMANAGER_H

#include <memory>
#include "../Components/Layout/Layout.h"
#include "../Components/TopMenu/TopMenu.h"

namespace Trema::View
{
    class Activity;
    class IStateManager
    {
    public:
        virtual std::shared_ptr<Layout> GetLayout() = 0;
        virtual std::shared_ptr<TopMenu> GetTopMenu() = 0;
        virtual std::unique_ptr<Activity>& Top() = 0;
        virtual std::unique_ptr<Activity> Pop() = 0;
        virtual void Push(std::unique_ptr<Activity> item) = 0;
        virtual void PushPending(std::unique_ptr<Activity> item) = 0;
        virtual bool Empty() = 0;
        virtual size_t Count() = 0;
        virtual void Clear() = 0;
        virtual void Wait() = 0;
        virtual void Update() = 0;
    };
}

#endif //TREMA_PROJECT_ISTATEMANAGER_H
