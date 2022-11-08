//
// Created by Benjam on 11/7/2022.
//

#ifndef TREMA_WINDOWBUILDER_H
#define TREMA_WINDOWBUILDER_H

#include "Window.h"
#include "WindowAsBase.h"
#include "../Activities/Activity.h"
#include "../Style/Parser/StackedStyleParser.h"
#include "../Parser/TinyXML/TinyXMLViewParser.h"

namespace Trema::View
{
    template<class W> requires WindowAsBase<W>
    class WindowBuilder
    {
    public:
        WindowBuilder() :
            m_mistakes(),
            m_window(std::make_shared<W>(
                    WindowInfo(),
                    std::make_unique<TinyXMLViewParser>(std::make_unique<StackedStyleParser>(m_mistakes), m_mistakes))
                    )
        {

        }

        template<class P> requires PopupAsBase<P>
        WindowBuilder& WithPopupComponent(std::shared_ptr<P> popupComponent)
        {
            m_window->template AddPopupComponent<P>(std::move(popupComponent));
            return *this;
        }

        WindowBuilder& WithIcon(const std::string& path)
        {
            m_window->SetWindowIcon(path);
            return *this;
        }

        WindowBuilder& WithDimension(int width, int height)
        {
            m_window->SetSize(width, height);
            return *this;
        }

        WindowBuilder& WithWidth(int width)
        {
            m_window->SetWidth(width);
            return *this;
        }

        WindowBuilder& WithHeight(int height)
        {
            m_window->SetHeight(height);
            return *this;
        }

        WindowBuilder& WithTitle(const std::string& title)
        {
            m_window->SetTitle(title);
            return *this;
        }

        WindowBuilder& WithErrorsOutput(bool toggle)
        {
            m_window->ToggleErrorsOutput(toggle);
            return *this;
        }

        WindowBuilder& WithActivity(std::unique_ptr<Activity> activity)
        {
            m_window->StartActivityForResult(std::move(activity));
            return *this;
        }

        std::shared_ptr<W> Build()
        {
            return m_window;
        }

    private:
        std::shared_ptr<W> m_window;
        MistakesContainer m_mistakes;
    };
}


#endif //TREMA_WINDOWBUILDER_H
