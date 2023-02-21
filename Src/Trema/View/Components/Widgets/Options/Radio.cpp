#include "Radio.h"
#include <imgui.h>
#include <utility>
#include <future>

namespace Trema::View
{
    Radio::Radio(std::shared_ptr<GuiElement> parent, std::string name) :
            Container(std::move(parent), std::move(name))
    {

    }

    Radio::~Radio()
    {

    }

    void Radio::AddOption(std::string name)
    {
        m_options.push_back(std::move(name));
    }

    void Radio::AddOnClickListener(std::string name, std::function<void(const std::string &)> function)
    {
        m_listeners[std::move(name)] = std::move(function);
    }

    void Radio::Show()
    {
        BeginStyle();
        int count = 0;
        bool changed = false;
        for(const auto& option : m_options)
        {
            if(count != 0 && Style.GetOrientation() == Row)
                ImGui::SameLine();

            if(ImGui::RadioButton(option.c_str(), &m_option, count ++))
            {
                changed = true;
            }
        }

        if(changed)
        {
            auto future = std::async(std::launch::async, [this]()
            {
                for(const auto& listener : m_listeners)
                {
                    listener.second(m_options[m_option]);
                }
            });
        }
        EndStyle();
    }

    std::shared_ptr<Radio> Radio::CreateRadio(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<Radio>(std::move(parent), std::move(name));
    }

    void Radio::AddChild(std::shared_ptr<GuiElement> child)
    {
        //if(IsType<Radio>(child))
        AddOption(child->GetName());
    }
}