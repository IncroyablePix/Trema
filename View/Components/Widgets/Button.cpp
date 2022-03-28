//
// Created by JajaFil on 2/14/2022.
//

#include <future>
#include "Button.h"

namespace Trema::View
{

    Button::Button(std::shared_ptr<IGuiElement> parent, std::string name) :
            IGuiElement(std::move(parent), std::move(name))
    {

    }

    Button::~Button()
    {

    }

    void Button::AddOnClickListener(std::string name, std::function<void(const Button &)> function)
    {
        m_listeners[std::move(name)] = std::move(function);
    }

    void Button::Show()
    {
        BeginStyle();
        if(ImGui::Button(NameId()))
        {
            auto future = std::async(std::launch::async, [this]()
            {
                for(const auto& [name, function] : m_listeners)
                {
                    function(*this);
                }
            });
        }
        EndStyle();
    }

    std::shared_ptr<Button> Button::CreateButton(std::shared_ptr<IGuiElement> parent, std::string name)
    {
        return std::make_shared<Button>(std::move(parent), std::move(name));
    }
}