#ifndef TREMA_PROJECT_ISTATEMANAGER_H
#define TREMA_PROJECT_ISTATEMANAGER_H

#include <memory>
#include "../Components/Layout/Layout.h"
#include "../Components/TopMenu/TopMenu.h"
#include "Intent.h"

namespace Trema::View
{
    class Activity;
    class IStateManager
    {
    public:
        virtual ~IStateManager() = default;
        virtual std::shared_ptr<Layout> GetLayout() = 0;
        virtual std::shared_ptr<TopMenu> GetTopMenu() = 0;
        virtual std::unique_ptr<Activity>& Top() = 0;
        virtual std::unique_ptr<Activity> Pop() = 0;
        virtual void Push(std::unique_ptr<Activity> item) = 0;
        virtual void PushPending(std::unique_ptr<Activity> item) = 0;
        virtual void QuitPending(uint16_t requestCode, uint16_t resultCode, Intent intent) = 0;
        virtual bool Empty() = 0;
        virtual size_t Count() = 0;
        virtual void Clear() = 0;
        virtual void Wait() = 0;
        virtual void UpdateState() = 0;
        virtual void UpdateCurrentActivity(double deltaTime) = 0;
    };
}

#endif //TREMA_PROJECT_ISTATEMANAGER_H
