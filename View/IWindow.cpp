//
// Created by JajaFil on 2/12/2022.
//

#include "IWindow.h"

namespace Trema::View
{
    IWindow::IWindow(const WindowInfo &info) :
            m_secondsPerUpdate(info.SecondsPerUpdate),
            m_height(info.Height),
            m_width(info.Width),
            m_standardFont(nullptr)
    {
    }

    void IWindow::SetLayout(std::shared_ptr<ILayout> layout)
    {
        m_layout = std::move(layout);
    }

    void IWindow::SetTopMenu(std::shared_ptr<TopMenu> topMenu)
    {
        m_menu = std::move(topMenu);
    }

    void IWindow::SetDefaultFont(const std::string &m_path, float size)
    {
        ImGuiIO& io = ImGui::GetIO();

        static const ImWchar ranges[] =
        {
                0x0020, 0x00FF, // Basic Latin + Latin Supplement
                0x20AC, 0x20AC, // €
                0x2122, 0x2122, // ™
                0x2196, 0x2196, // ↖
                0x21D6, 0x21D6, // ⇖
                0x2B01, 0x2B01, // ⬁
                0x2B09, 0x2B09, // ⬉
                0x2921, 0x2922, // ⤡ ⤢
                0x263A, 0x263A, // ☺
                0x266A, 0x266A, // ♪
                0,
        };

        m_standardFont = io.Fonts->AddFontFromFileTTF(m_path.c_str(), size, nullptr, io.Fonts->GetGlyphRangesDefault());
    }

    void IWindow::Build()
    {
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->Build();
        // io.Fonts->GetTexDataAsRGBA32();
    }
}