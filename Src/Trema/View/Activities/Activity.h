#ifndef TREMA_PROJECT_ACTIVITY_H
#define TREMA_PROJECT_ACTIVITY_H

#include "Intent.h"
#include "ActivityAsBase.h"
#include <string>
#include <memory>
#include "../Windowing/Window.h"

namespace Trema::View
{
    class Activity
    {
    public:
        Activity(Intent intent, uint16_t requestCode = -1);
        virtual ~Activity() = default;

        // To be overriden
        virtual void OnActivityStart();
        virtual void OnCreateView();
        virtual void OnActivityEnd();
        virtual void OnActivityResume();
        virtual void OnActivityResult(uint16_t requestCode, uint16_t resultCode, Intent intent);
        virtual void OnActivityUpdate(double deltaTime);

        void ApplyStyle();
        void SetLayout(std::shared_ptr<Layout> layout);
        void SetTopMenu(std::shared_ptr<TopMenu> topMenu);
        inline std::shared_ptr<Layout> GetLayout() const { return m_layout; }
        inline std::shared_ptr<TopMenu> GetTopMenu() const { return m_menu; }
        void SetDefaultFont(const std::string &name);
        void Resume();
        void ToggleFullscreen(bool fullscreen);
        void SetSize(int width, int height);
        void SetWindow(std::shared_ptr<Window> window);

        template<class T> std::shared_ptr<T> GetElementById(const std::string& id)
        {
            if(!m_elementsById.contains(id))
                return nullptr;

            auto element = m_elementsById.at(id);

            if(!dynamic_cast<T*>(element.get()))
                return nullptr;

            return std::dynamic_pointer_cast<T>(element);
        }

        template<class T> requires ActivityAsBase<T>
        void StartActivityForResult(ActivityBuilder<T> activityBuilder, uint16_t requestCode, Intent intent)
        {
            auto activity = activityBuilder.CreateActivity(std::move(intent), requestCode);
            if(m_window)
                activity->SetWindow(m_window);

            m_window->StartActivityForResult(std::move(activity));
        }

        template<class T> requires ActivityAsBase<T>
        void StartActivityForResult(ActivityBuilder<T> activityBuilder, uint16_t requestCode)
        {
            auto activity = activityBuilder.CreateActivity(Intent {}, requestCode);
            if(m_window)
                activity->SetWindow(m_window);

            m_window->StartActivityForResult(std::move(activity));
        }

        template<class T> requires ActivityAsBase<T>
        void StartActivityForResult(uint16_t requestCode, Intent intent)
        {
            auto activityBuilder = ActivityBuilder<T>();
            StartActivityForResult(std::move(activityBuilder), requestCode, std::move(intent));
        }

        template<class T> requires ActivityAsBase<T>
        void StartActivityForResult(uint16_t requestCode)
        {
            auto activityBuilder = ActivityBuilder<T>();
            StartActivityForResult(std::move(activityBuilder), requestCode);
        }

        template<class T> requires ActivityAsBase<T>
        void StartActivity()
        {
            auto activityBuilder = ActivityBuilder<T>();
            StartActivityForResult(std::move(activityBuilder), -1);
        }

        inline void AddElementId(const std::string& id, std::shared_ptr<GuiElement> element)
        {
            m_elementsById[id] = std::move(element);
        }

        ElementStyle Style;

    protected:
        // Intent passthrough
        std::string GetStringExtra(const std::string& name);
        uint64_t GetUint64Extra(const std::string& name);
        uint32_t GetUint32Extra(const std::string& name);
        uint16_t GetUint16Extra(const std::string& name);
        uint8_t GetUint8Extra(const std::string& name);

        int64_t GetInt64Extra(const std::string& name);
        int32_t GetInt32Extra(const std::string& name);
        int16_t GetInt16Extra(const std::string& name);
        int8_t GetInt8Extra(const std::string& name);

        float GetFloatExtra(const std::string& name);
        double GetDoubleExtra(const std::string& name);
        bool GetBoolExtra(const std::string& name);
        char8_t GetCharExtra(const std::string& name);

        RawIntentValue GetExtra(const std::string& name);

        template<class T> std::shared_ptr<T> GetComponent()
        {
            return m_window->GetComponent<T>();
        }

        void LoadView(const std::string &path);
        void QuitApplication() const;
        void QuitActivity(uint16_t requestCode, uint16_t resultCode = 0, Intent intent = Intent {}) const;
        void QuitActivity(uint16_t resultCode = 0, Intent intent = Intent {}) const;

    private:
        std::unordered_map<std::string, std::shared_ptr<GuiElement>> m_elementsById;
        Intent m_intent;
        std::shared_ptr<Window> m_window;
        std::shared_ptr<Layout> m_layout;
        std::shared_ptr<TopMenu> m_menu;

        bool m_fullscreen { false };
        int m_width;
        int m_height;

    private:

        uint16_t m_requestCode;
    };
}

#endif //TREMA_PROJECT_ACTIVITY_H
