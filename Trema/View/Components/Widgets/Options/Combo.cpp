//
// Created by JajaFil on 2/14/2022.
//

#include <future>
#include "Combo.h"
#include "../../../ImGUI/imgui.h"

namespace Trema::View
{

    Combo::Combo(std::shared_ptr<GuiElement> parent, std::string name) :
            IContainer(std::move(parent), std::move(name)),
            m_selected("")
    {

    }

    Combo::~Combo()
    {

    }

    void Combo::AddChild(std::shared_ptr<GuiElement> child)
    {
        AddOption(child->GetName());
    }

    void Combo::AddOption(std::string name)
    {
        m_options.push_back(std::move(name));
    }

    void Combo::Show()
    {
        /*ImGuiComboFlags flags = 0;
        ImGui::CheckboxFlags("ImGuiComboFlags_PopupAlignLeft", (unsigned int*)&flags, ImGuiComboFlags_PopupAlignLeft);
        //ImGui::SameLine(); HelpMarker("Only makes a difference if the popup is larger than the combo");
        if (ImGui::CheckboxFlags("ImGuiComboFlags_NoArrowButton", (unsigned int*)&flags, ImGuiComboFlags_NoArrowButton))
        {
            flags &= ~ImGuiComboFlags_NoPreview;     // Clear the other flag, as we cannot combine both
        }
        if (ImGui::CheckboxFlags("ImGuiComboFlags_NoPreview", (unsigned int*)&flags, ImGuiComboFlags_NoPreview))
        {
            flags &= ~ImGuiComboFlags_NoArrowButton; // Clear the other flag, as we cannot combine both
        }*/

        BeginStyle();
        if (ImGui::BeginCombo(NameId(), m_selected))
        {
            for(const auto& name : m_options)
            {
                bool selected = m_selected == name;

                if(ImGui::Selectable(name.c_str(), selected))
                {
                    m_selected = name.c_str();

                    auto future = std::async(std::launch::async, [this]()
                    {
                        for(const auto& [_, listener] : m_listeners)
                        {
                            listener(m_selected);
                        }
                    });
                }

                if(selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }
        EndStyle();
    }

    std::shared_ptr<Combo> Combo::CreateCombo(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<Combo>(std::move(parent), std::move(name));
    }

    void Combo::AddOnClickListener(std::string name, std::function<void(const std::string &)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }
}