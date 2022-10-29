//
// Created by JajaFil on 5/22/2022.
//

#ifndef TREMA_PROJECT_THREADSAFESTATEMANAGER_H
#define TREMA_PROJECT_THREADSAFESTATEMANAGER_H

#include <stack>
#include <mutex>
#include <condition_variable>
#include "Activity.h"
#include "IStateManager.h"

namespace Trema::View
{
    struct EndStruct
    {
        uint16_t RequestCode;
        uint16_t ResultCode;
        Intent Intent;
    };

    class ThreadSafeStateManager : public IStateManager
    {
    public:
        ThreadSafeStateManager() = default;
        ThreadSafeStateManager(const ThreadSafeStateManager&) = delete;
        ~ThreadSafeStateManager() override;

        inline std::shared_ptr<Layout> GetLayout() override { return Top()->GetLayout(); }
        inline std::shared_ptr<TopMenu> GetTopMenu() override { return Top()->GetTopMenu(); }
        std::unique_ptr<Activity>& Top() override;
        std::unique_ptr<Activity> Pop() override;
        void Push(std::unique_ptr<Activity> item) override;
        void PushPending(std::unique_ptr<Activity> item) override;
        bool Empty() override;
        size_t Count() override;
        void Clear() final;
        void Wait() override;
        void UpdateState() override;
        void UpdateCurrentActivity(double deltaTime) override;
        void QuitPending(uint16_t requestCode, uint16_t resultCode, Intent intent) override;

    private:
        std::stack<std::unique_ptr<Activity>> m_activities;

        std::mutex m_mutex;
        std::mutex m_mutexBlocking;
        std::condition_variable m_blocking;

        std::unique_ptr<Activity> m_toLoad { nullptr };
        std::unique_ptr<EndStruct> m_toQuit { nullptr };
    };
}

#endif //TREMA_PROJECT_THREADSAFESTATEMANAGER_H
