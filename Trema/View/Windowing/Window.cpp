//
// Created by JajaFil on 2/12/2022.
//

#include "Window.h"

#include <memory>
#include "../ImGUI/imgui_impl_vulkan.h"
#include "../Utils/FileSplits.h"

#ifdef WIN32
#include "windows.h"
#include "Fonts/FontsRepository.h"
#include "Vulkan/VulkanImage.h"

#endif

namespace Trema::View
{
    Window::Window(const WindowInfo &info) :
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

    void Window::SetLayout(std::shared_ptr<Layout> layout)
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

        if(!FontsRepository::GetInstance()->Exists(name))
            m_standardFont = nullptr;

        m_standardFont = (*FontsRepository::GetInstance())[name].Font;
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
        FontsRepository::GetInstance()->AddFont(name, path, size, nullptr);
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

        if(Style.WidgetBackgroundColorHover().HasColor())
            style->Colors[ImGuiCol_FrameBgHovered] = Style.WidgetBackgroundColorHover().GetColor();

        if(Style.WidgetBackgroundColorActive().HasColor())
            style->Colors[ImGuiCol_FrameBgActive] = Style.WidgetBackgroundColorActive().GetColor();

        if(Style.ButtonColor().HasColor())
            style->Colors[ImGuiCol_Button] = Style.ButtonColor().GetColor();

        if(Style.ButtonColorHover().HasColor())
            style->Colors[ImGuiCol_ButtonHovered] = Style.ButtonColorHover().GetColor();

        if(Style.ButtonColorActive().HasColor())
            style->Colors[ImGuiCol_ButtonActive] = Style.ButtonColorActive().GetColor();

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

        if(Style.SliderGrabColor().HasColor())
            style->Colors[ImGuiCol_SliderGrab] = Style.SliderGrabColor().GetColor();

        if(Style.SliderGrabActiveColor().HasColor())
            style->Colors[ImGuiCol_SliderGrabActive] = Style.SliderGrabActiveColor().GetColor();

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

    std::shared_ptr<IRenderImage> Window::AddImage(const std::string &image, const std::string &source)
    {
        auto renderImage = std::make_shared<VulkanImage>(source, m_renderer);
        m_renderImages[image] = renderImage;

        return renderImage;
    }
}
