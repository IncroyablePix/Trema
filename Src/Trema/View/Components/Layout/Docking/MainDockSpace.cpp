//
// Created by Benjam on 10/20/2021.
//

#include "MainDockSpace.h"

#include <utility>
#include <imgui.h>
#include <imgui_internal.h>

namespace Trema::View
{
    MainDockSpace::MainDockSpace(std::string title, bool allowSave) :
            DockSpace(std::move(title), allowSave)
    {

    }

    void MainDockSpace::Show()
    {
        const auto& io = ImGui::GetIO();
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;

        const auto* viewport = ImGui::GetMainViewport();

        Begin();

        if(io.ConfigFlags & ImGuiConfigFlags_DockingEnable) // If docking enabled
        {
            ImGuiID dockspaceId = ImGui::GetID(NameId());
            ImGui::DockSpace(dockspaceId, ImVec2(0.0f, 0.0f), dockspaceFlags);

            if (m_firstTime && !IsSavedDock())
            {
                m_firstTime = false;

                ImGui::DockBuilderRemoveNode(dockspaceId); // clear any previous layout
                ImGui::DockBuilderAddNode(dockspaceId, dockspaceFlags | ImGuiDockNodeFlags_DockSpace);
                ImGui::DockBuilderSetNodeSize(dockspaceId, viewport->Size);

                ShowElements(dockspaceId);

                ImGui::DockBuilderFinish(dockspaceId);
            }
        }

        End();
    }

    void MainDockSpace::Begin()
    {
        BeginStyle();
        const auto* viewport = ImGui::GetMainViewport();
        // Central dockspace should take up all space
        ImGui::SetNextWindowPos(viewport->Pos);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowViewport(viewport->ID);

        ImGuiWindowFlags windowFlags = (m_hasMenuBar ? ImGuiWindowFlags_MenuBar : 0) |
                                       ImGuiWindowFlags_NoDocking |
                                       ImGuiWindowFlags_NoTitleBar |
                                       ImGuiWindowFlags_NoCollapse |
                                       ImGuiWindowFlags_NoResize |
                                       ImGuiWindowFlags_NoMove |
                                       ImGuiWindowFlags_NoBringToFrontOnFocus |
                                       ImGuiWindowFlags_NoNavFocus;

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { .0f, .0f });
        ImGui::Begin(NameId(), nullptr, windowFlags);
    }

    void MainDockSpace::End()
    {
        ImGui::End();
        ImGui::PopStyleVar(1);

        for(const auto& [slot, element] : m_elements)
        {
            element->Show();
        }
        EndStyle();
    }

    std::shared_ptr <MainDockSpace> MainDockSpace::CreateMainDockSpace(std::string title, bool saveLayout)
    {
        return std::make_shared<MainDockSpace>(std::move(title), saveLayout);
    }
}