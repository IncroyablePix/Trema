#include "Window.h"

#include <memory>
#include <iostream>
#include "Fonts/FontsRepository.h"
#include "Vulkan/VulkanImage.h"
#include "../Parser/ViewParser.h"
#include "../Activities/ThreadSafeStateManager.h"


namespace Trema::View
{
    Window::Window(const WindowInfo &info, std::unique_ptr<ViewParser> viewParser) :
            m_height(info.Height),
            m_width(info.Width),
            m_standardFont(nullptr),
            m_opened(false),
            m_viewParser(std::move(viewParser)),
            m_stateManager(std::make_unique<ThreadSafeStateManager>())
    {
    }

    void Window::SetDefaultFont(const std::string &name)
    {
        if(!FontsRepository::GetInstance()->Exists(name))
            m_standardFont = nullptr;

        m_standardFontName = name;
        m_standardFont = (*FontsRepository::GetInstance())[name].Font;
    }

    void Window::UploadFonts()
    {
        m_renderer->UploadFonts();
    }

    int Window::Run()
    {
        m_opened = true;

        m_stateManager->UpdateState();
        UploadFonts();
        while(IsOpened())
        {
            Update();
        }

        return 0;
    }

    void Window::AddFont(const std::string &path, float size, const std::string& name)
    {
        FontsRepository::GetInstance()->AddFont(name, path, size, nullptr);
    }

    void Window::Build()
    {
        BuildFontAtlas();
    }

    void Window::LoadView(const std::string &path, std::shared_ptr<Window> window)
    {
        if(!m_stateManager->Empty())
        {
            m_viewParser->LoadView(path, std::move(window), *m_stateManager->Top());

            if(m_displayErrors)
            {
                std::cerr << m_viewParser->GetMistakes() << std::flush;
            }
        }
    }

    void Window::StartActivityForResult(std::unique_ptr<Activity> activity)
    {
        m_stateManager->PushPending(std::move(activity));
    }

    void Window::BuildFontAtlas()
    {
        ImGuiIO& io = ImGui::GetIO();

        io.Fonts->Build();

        FontsRepository::GetInstance()->ReloadFonts();
        if(!m_standardFontName.empty())
        {
            m_standardFont = (*FontsRepository::GetInstance())[m_standardFontName].Font;
        }

        UploadFonts();
    }

    void Window::InitializeDearImGUI() const
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        // ImPlot::CreateContext();
        auto& io = ImGui::GetIO(); (void) io;
        io.Fonts->AddFontDefault();

        io.DisplaySize.x = static_cast<float>(m_width);
        io.DisplaySize.y = static_cast<float>(m_height);
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    }

    void Window::Resize(int width, int height)
    {
        m_width = width;
        m_height = height;
    }

    void Window::ConsumePostRenderRoutines()
    {
        while(!m_postRenderRoutines.empty())
        {
            m_postRenderRoutines.front()();
            m_postRenderRoutines.pop_front();
        }
    }

    void Window::Update()
    {
        UpdateTime();
        m_stateManager->UpdateState();
        PollEvent();
        Render();
        ConsumePostRenderRoutines();
    }

    void Window::InitializeVulkan(std::shared_ptr<IWindowBackendStrategy> windowBackendStrategy)
    {
        m_renderer = std::make_shared<VulkanRenderer>(windowBackendStrategy);
        m_windowBackendStrategy = std::move(windowBackendStrategy);
    }

    void Window::Close()
    {
        m_opened = false;
    }

    bool Window::IsOpened() const
    {
        return m_opened;
    }

    void Window::Render()
    {
        if(m_stateManager->Empty())
        {
            Close();
            return;
        }

        auto* wd = m_renderer->GetWindowData();

        ImGui_ImplVulkan_NewFrame();
        m_windowBackendStrategy->BeginNewFrame();
        ImGui::NewFrame();

        if(m_standardFont)
            ImGui::PushFont(m_standardFont);

        //--- ImGui code

        m_stateManager->UpdateCurrentActivity(m_deltaTime);
        auto menu = m_stateManager->GetTopMenu();
        if(menu)
        {
            menu->Show();
        }

        if(auto layout = m_stateManager->GetLayout())
        {
            layout->SetActiveMenuBar(menu != nullptr);
            layout->Show();
        }

        for(const auto& [name, popup] : m_popupComponents)
            popup->Show();

        //---

        if(m_standardFont)
            ImGui::PopFont();

        ImGui::Render();
        ImDrawData* drawData = ImGui::GetDrawData();

        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
        }

        const bool isMinimized = (drawData->DisplaySize.x <= 0.0f || drawData->DisplaySize.y <= 0.0f);
        if(!isMinimized)
        {
            m_renderer->Clear();
            m_renderer->Render(wd, drawData);
            m_renderer->FramePresent(wd);
            SwapBuffers();
        }
    }

    std::shared_ptr<IRenderImage> Window::AddImage(const std::string &image, const std::string &source)
    {
        auto renderImage = std::make_shared<VulkanImage>(source, m_renderer);
        m_renderImages[image] = renderImage;

        return renderImage;
    }

    void Window::QuitActivity(uint16_t requestCode, uint16_t resultCode, Intent intent)
    {
        m_stateManager->QuitPending(requestCode, resultCode, std::move(intent));
    }
}
