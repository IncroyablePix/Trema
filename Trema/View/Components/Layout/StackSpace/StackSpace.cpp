//
// Created by JajaFil on 3/29/2022.
//

#include "StackSpace.h"

#include <utility>

namespace Trema::View
{
    StackSpace::StackSpace(std::string title) :
        ILayout(std::move(title))
    {

    }

    StackSpace::~StackSpace()
    {

    }

    void StackSpace::Show()
    {
        Begin();

        for(const auto& container : m_elements)
            for(const auto& element : container->GetChildren())
                element->Show();

        End();
    }

    std::shared_ptr<StackSpace> StackSpace::CreateStackSpace(std::string title)
    {
        return std::make_shared<StackSpace>(std::move(title));
    }

    void StackSpace::Begin()
    {
        BeginStyle();

        auto* viewport = ImGui::GetMainViewport();
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

    void StackSpace::AddContainer(std::shared_ptr<IContainer> container,
                                  std::unordered_map<std::string, std::string> &attributes,
                                  const std::shared_ptr<IWindow> &window)
    {
        if(container)
            m_elements.push_back(std::move(container));
    }
}