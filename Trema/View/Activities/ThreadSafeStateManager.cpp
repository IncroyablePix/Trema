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
        std::unique_ptr<Activity> t = std::move(m_activities.top());
        m_activities.pop();
        return t;
    }

    void ThreadSafeStateManager::Push(std::unique_ptr<Activity> item)
    {
        {
            std::scoped_lock lock(m_mutex);
            m_activities.push(std::move(item));

            std::unique_lock<std::mutex> ul(m_mutexBlocking);
            m_blocking.notify_one();
        }

        //ImGui::GetIO().Fonts->ClearFonts();
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
            std::unique_lock<std::mutex> ul(m_mutexBlocking);
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

    void ThreadSafeStateManager::Update()
    {
        if(m_toLoad)
        {
            Push(std::move(m_toLoad));
            m_toLoad.reset();
        }
    }
}