//
// Created by Benjam on 10/20/2021.
//

#include <utility>
#include <fstream>
#include "DockSpace.h"
#include "../../../Exceptions/ParsingException.h"
#include "../LayoutException.h"
#include "../../../Windowing/Window.h"

namespace Trema::View
{
    DockSpace::DockSpace(std::string title, bool allowSave) :
            Layout(std::move(title)),
            m_allowSave(allowSave)
    {

    }

    void DockSpace::AddElement(std::shared_ptr<Container> element, DockSlot slot)
    {
        m_elements[slot] = std::move(element);
    }

    void DockSpace::Show()
    {
        auto const& io = ImGui::GetIO();
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        Begin();

        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) // If docking enabled
        {
            auto wSize = ImGui::GetWindowSize();
            ImGuiID dockspaceId = ImGui::GetID(NameId());
            ImGui::DockSpace(dockspaceId, ImVec2(), dockspaceFlags);

            if (m_firstTime && !IsSavedDock())
            {
                m_firstTime = false;

                ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
                ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_CentralNode);
                ImGui::DockBuilderSetNodeSize(dockspaceId, wSize);

                ShowElements(dockspaceId);

                ImGui::DockBuilderFinish(dockspaceId);
            }
        }

        End();
    }

    void DockSpace::ShowElements(ImGuiID dockspaceId) const
    {
        for(const auto& [slot, element] : m_elements)
        {
            if(slot != DOCK_CENTER)
            {
                auto dock = ImGui::DockBuilderSplitNode(dockspaceId, slot, element->GetDockSize(), nullptr, &dockspaceId);
                ImGui::DockBuilderDockWindow(element->NameId(), dock);
            }
            else
            {
                ImGui::DockBuilderDockWindow(element->NameId(), dockspaceId);
            }
        }
    }

    void DockSpace::Begin()
    {
        ImGuiWindowFlags windowFlags = (m_hasMenuBar ? ImGuiWindowFlags_MenuBar : 0) |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin(m_name.c_str(), nullptr, windowFlags);
    }

    void DockSpace::End()
    {
        ImGui::End();

        for(const auto& [slot, element] : m_elements)
        {
            if(slot != DOCK_CENTER)
            {
                element->Show();
            }
        }
    }

    std::shared_ptr<DockSpace> DockSpace::CreateDockSpace(std::string title, ImGuiID dockspaceId)
    {
        return std::make_shared<DockSpace>(std::move(title), dockspaceId);
    }

    bool DockSpace::IsSavedDock() const
    {
        auto const& io = ImGui::GetIO();
        std::ifstream file(io.IniFilename);

        return file.is_open() && m_allowSave;
    }

    void DockSpace::AddContainer(std::shared_ptr<Container> container,
                                 std::unordered_map<std::string, std::string> &attributes)
    {
        if(!attributes.contains("dockSlot"))
            throw LayoutException(R"(Missing attribute "dockSlot" for DockSpace child)");

        auto dockSlotName = attributes["dockSlot"];
        auto dockSlot = DockSlotFromString(dockSlotName);

        AddElement(std::move(container), dockSlot);
    }

    //---

    DockSlot DockSlotFromString(const std::string_view &name)
    {
        if(name == "top")
            return DOCK_TOP;
        else if(name == "bottom")
            return DOCK_BOTTOM;
        else if(name == "left")
            return DOCK_LEFT;
        else if(name == "right")
            return DOCK_RIGHT;

        return DOCK_CENTER;
    }
}