//
// Created by JajaFil on 2/12/2022.
//

#include "Window.h"

#include <memory>
#include "../ImGUI/imgui_impl_vulkan.h"
#include "../Utils/FileSplits.h"

#ifdef WIN32
#include "windows.h"
#endif

namespace Trema::View
{
    Window::Window(const WindowInfo &info) :
            m_secondsPerUpdate(info.SecondsPerUpdate),
            m_height(info.Height),
            m_width(info.Width),
            m_standardFont(nullptr),
            m_opened(false)
    {
#ifdef WIN32
        SetConsoleOutputCP(65001); // UTF-8
        ShowWindow(GetConsoleWindow(), SW_HIDE); // Hide Windows terminal
#endif
    }

    void Window::SetLayout(std::shared_ptr<ILayout> layout)
    {
        m_layout = std::move(layout);
    }

    void Window::SetTopMenu(std::shared_ptr<TopMenu> topMenu)
    {
        m_menu = std::move(topMenu);
    }

    void Window::SetDefaultFont(const std::string &name)
    {
        ImGuiIO& io = ImGui::GetIO();

        if(m_fonts.find(name) == m_fonts.end())
            m_standardFont = nullptr;

        m_standardFont = m_fonts[name];
    }

    void Window::UploadFonts()
    {
        m_renderer->UploadFonts();
    }

    int Window::Run()
    {
        m_opened = true;
        Build();
        UploadFonts();
        while(IsOpened())
        {
            Update();
        }

        return 0;
    }

    void Window::AddFont(const std::string &path, float size, const std::string& name)
    {
        ImGuiIO& io = ImGui::GetIO();

        static const ImWchar ranges[] =
        {
                0x0020, 0x00FF, // Basic Latin + Latin Supplement
                0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
                0x20AC, 0x20AC, // €
                0x2122, 0x2122, // ™
                0x2196, 0x2196, // ↖
                0x21D6, 0x21D6, // ⇖
                0x2B01, 0x2B01, // ⬁
                0x2B09, 0x2B09, // ⬉
                0x2921, 0x2922, // ⤡ ⤢
                0x263A, 0x263A, // ☺
                0x266A, 0x266A, // ♪
                0x2DE0, 0x2DFF, // Cyrillic Extended-A
                0xA640, 0xA69F, // Cyrillic Extended-B
                0,
        };

        auto font = io.Fonts->AddFontFromFileTTF(path.c_str(), size, nullptr, ranges);
        if(name.empty())
        {
            m_fonts[FileSplit(path).FileWithoutExtension] = font;
        }
        else
        {
            m_fonts[name] = font;
        }

    }

    void Window::Build()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Build();
        // io.Fonts->GetTexDataAsRGBA32();
    }

    void Window::ApplyStyle()
    {
        ImGuiStyle *style = &ImGui::GetStyle();

        style->WindowPadding = Style.GetWindowPadding();
        style->FramePadding = Style.GetFramePadding();
        style->WindowRounding = Style.GetWindowRounding();
        style->FrameRounding = Style.GetFrameRounding();

        //--- Colors
        if(Style.TextColor().HasColor())
            style->Colors[ImGuiCol_Text] = Style.TextColor().GetColor();

        if(Style.TextDisabledColor().HasColor())
            style->Colors[ImGuiCol_TextDisabled] = Style.TextDisabledColor().GetColor();

        if(Style.WindowColor().HasColor())
            style->Colors[ImGuiCol_WindowBg] = Style.WindowColor().GetColor();

        if(Style.WidgetBackgroundColor().HasColor())
            style->Colors[ImGuiCol_FrameBg] = Style.WidgetBackgroundColor().GetColor();

        if(Style.MenuBackgroundColor().HasColor())
            style->Colors[ImGuiCol_MenuBarBg] = Style.MenuBackgroundColor().GetColor();

        if(Style.HeaderColor().HasColor())
            style->Colors[ImGuiCol_TitleBg] = Style.HeaderColor().GetColor();

        if(Style.HeaderActiveColor().HasColor())
            style->Colors[ImGuiCol_TitleBgActive] = Style.HeaderActiveColor().GetColor();

        if(Style.TableHeaderColor().HasColor())
            style->Colors[ImGuiCol_TableHeaderBg] = Style.TableHeaderColor().GetColor();

        if(Style.PopupBackgroundColor().HasColor())
            style->Colors[ImGuiCol_PopupBg] = Style.PopupBackgroundColor().GetColor();

        if(!Style.GetFont().empty())
            SetDefaultFont(Style.GetFont());
    }

    void Window::InitializeDearImGUI() const
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void) io;
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

    void Window::Update()
    {
        PollEvent();
        Render();
    }

    void Window::InitializeVulkan(std::shared_ptr<IWindowBackendStrategy> windowBackendStrategy)
    {
        m_renderer = std::make_unique<VulkanRenderer>(windowBackendStrategy);
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
        auto* wd = m_renderer->GetWindowData();

        ImGui_ImplVulkan_NewFrame();
        m_windowBackendStrategy->BeginNewFrame();
        ImGui::NewFrame();

        if(m_standardFont)
            ImGui::PushFont(m_standardFont);

        //--- ImGui code
        if(m_menu)
        {
            m_menu->Show();
        }

        if(m_layout)
        {
            m_layout->SetActiveMenuBar(m_menu != nullptr);
            m_layout->Show();
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
        }
    }
}