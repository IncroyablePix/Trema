//
// Created by JajaFil on 2/12/2022.
//

#include "IWindow.h"
#include "ImGUI/imgui_impl_vulkan.h"
#include "Utils/FileSplits.h"

#ifdef WIN32
#include "windows.h"
#endif

namespace Trema::View
{
    IWindow::IWindow(const WindowInfo &info) :
            m_secondsPerUpdate(info.SecondsPerUpdate),
            m_height(info.Height),
            m_width(info.Width),
            m_standardFont(nullptr)
    {
#ifdef WIN32
        SetConsoleOutputCP(65001); // UTF-8
#endif
    }

    void IWindow::SetLayout(std::shared_ptr<ILayout> layout)
    {
        m_layout = std::move(layout);
    }

    void IWindow::SetTopMenu(std::shared_ptr<TopMenu> topMenu)
    {
        m_menu = std::move(topMenu);
    }

    void IWindow::SetDefaultFont(const std::string &name)
    {
        ImGuiIO& io = ImGui::GetIO();

        if(m_fonts.find(name) == m_fonts.end())
            m_standardFont = nullptr;

        m_standardFont = m_fonts[name];
    }

    void IWindow::AddFont(const std::string &path, float size, const std::string& name)
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

    void IWindow::Build()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Build();
        // io.Fonts->GetTexDataAsRGBA32();
    }

    void IWindow::ApplyStyle()
    {
        ImGuiStyle *style = &ImGui::GetStyle();

        style->WindowPadding = Style.GetPadding();
        style->WindowRounding = Style.GetRounding();

        //--- Colors
        if(Style.HasTextColor())
            style->Colors[ImGuiCol_Text] = Style.GetTextColor();

        if(Style.HasBackgroundColor())
            style->Colors[ImGuiCol_WindowBg] = Style.GetBackgroundColor();

        if(Style.HasHeaderColor())
            style->Colors[ImGuiCol_TitleBg] = Style.GetHeaderColor();

        if(!Style.GetFont().empty())
            SetDefaultFont(Style.GetFont());
    }
}