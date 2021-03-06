//
// Created by JajaFil on 5/22/2022.
//

#include "ThreadSafeStateManager.h"
#include "Activity.h"

namespace Trema::View
{
    ThreadSafeStateManager::~ThreadSafeStateManager()
    {
        Clear();
    }

    std::unique_ptr<Activity>& ThreadSafeStateManager::Top()
    {
        std::scoped_lock lock(m_mutex);
        return m_activities.top();
    }

    std::unique_ptr<Activity> ThreadSafeStateManager::Pop()
    {
        std::scoped_lock lock(m_mutex);
        auto t = std::move(m_activities.top());
        m_activities.pop();

        if(!m_activities.empty())
        {
            m_activities.top()->Resume();
        }

        return t;
    }

    void ThreadSafeStateManager::UpdateCurrentActivity()
    {
        Top()->OnActivityUpdate();
    }

    void ThreadSafeStateManager::Push(std::unique_ptr<Activity> item)
    {
        {
            std::scoped_lock lock(m_mutex);
            m_activities.push(std::move(item));

            std::unique_lock ul(m_mutexBlocking);
            m_blocking.notify_one();
        }

        Top()->OnCreateView();
        Top()->OnActivityStart();
    }

    bool ThreadSafeStateManager::Empty()
    {
        std::scoped_lock<std::mutex> lock(m_mutex);
        return m_activities.empty();
    }

    size_t ThreadSafeStateManager::Count()
    {
        std::scoped_lock lock(m_mutex);
        return m_activities.size();
    }

    void ThreadSafeStateManager::Wait()
    {
        while(Empty())
        {
            std::unique_lock ul(m_mutexBlocking);
            m_blocking.wait(ul);
        }
    }

    void ThreadSafeStateManager::Clear()
    {
        while(!Empty())
        {
            Pop();
        }
    }

    void ThreadSafeStateManager::PushPending(std::unique_ptr<Activity> item)
    {
        m_toLoad = std::move(item);
    }

    void ThreadSafeStateManager::QuitPending(uint16_t requestCode, uint16_t resultCode, Intent intent)
    {
        m_toQuit = std::make_unique<EndStruct>();
        m_toQuit->RequestCode = requestCode;
        m_toQuit->ResultCode = resultCode;
        m_toQuit->Intent = std::move(intent);
    }

    void ThreadSafeStateManager::UpdateState()
    {
        if(m_toQuit)
        {
            auto toLeave = Pop();
            toLeave->OnActivityEnd();

            if(!Empty())
            {
                const auto& toResume = Top();
                toResume->OnActivityResult(m_toQuit->RequestCode, m_toQuit->ResultCode, std::move(m_toQuit->Intent));
                m_toQuit.reset();
            }
        }

        if(m_toLoad)
        {
            Push(std::move(m_toLoad));
            m_toLoad.reset();
        }
    }
}