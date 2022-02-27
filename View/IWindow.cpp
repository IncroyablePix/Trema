//
// Created by JajaFil on 2/12/2022.
//

#include "IWindow.h"

namespace Trema::View
{
    IWindow::IWindow(const WindowInfo &info) :
            m_secondsPerUpdate(info.SecondsPerUpdate),
            m_height(info.Height),
            m_width(info.Width)
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
}