//
// Created by JajaFil on 2/14/2022.
//

#include "Radio.h"
#include "../../ImGUI/imgui.h"

#include <utility>
#include <future>

namespace Trema::View
{
    Radio::Radio(std::shared_ptr<IGuiElement> parent, std::string name) :
        IGuiElement(std::move(parent), std::move(name))
    {

    }

    Radio::~Radio()
    {

    }

    void Radio::AddOption(std::string name, std::function<void(Radio)> listener)
    {
        RadioOption option = {.Name = std::move(name), .Listener = std::move(listener)};
        m_options.push_back(option);
    }

    void Radio::Show()
    {
        int count = 0;
        for(const auto& option : m_options)
        {
            if(count != 0 && Style.Orientation == Row)
                ImGui::SameLine();

            if(ImGui::RadioButton(option.Name.c_str(), &m_option, count ++))
            {
                auto future = std::async(std::launch::async, [this, &option]()
                {
                    option.Listener(*this);
                });
            }
        }
    }

    std::shared_ptr<Radio> Radio::CreateRadio(std::shared_ptr<IGuiElement> parent, std::string name)
    {
        return std::make_shared<Radio>(std::move(parent), std::move(name));
    }
}