//
// Created by JajaFil on 3/29/2022.
//

#include "StackSpace.h"

#include <utility>

namespace Trema::View
{
    StackSpace::StackSpace(std::string title) :
            Layout(std::move(title))
    {

    }

    void StackSpace::Show()
    {
        Begin();

        ImGui::Columns((int)m_elements.size(), NameId());
        for(const auto& container : m_elements)
        {
            Container::ToggleSubContainerization(true);
            container->Show();
            Container::ToggleSubContainerization(false);

            ImGui::NextColumn();
        }

        End();
    }

    std::shared_ptr<StackSpace> StackSpace::CreateStackSpace(std::string title)
    {
        return std::make_shared<StackSpace>(std::move(title));
    }

    void StackSpace::Begin()
    {
        BeginStyle();

        const auto* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags = (m_hasMenuBar ? ImGuiWindowFlags_MenuBar : 0) |
                                       ImGuiWindowFlags_NoDocking |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;

        ImGui::Begin(NameId(), nullptr, windowFlags);
    }

    void StackSpace::End()
    {
        ImGui::End();
        EndStyle();
    }

    void StackSpace::AddContainer(std::shared_ptr<Container> container,
                                  std::unordered_map<std::string, std::string> &attributes)
    {
        if(container)
            m_elements.push_back(std::move(container));
    }
}