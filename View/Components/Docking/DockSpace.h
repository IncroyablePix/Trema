//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_DOCKSPACE_H
#define MATH4BG_DOCKSPACE_H

#include <string>
#include <array>
#include <memory>
#include <unordered_map>
#include "../IGuiElement.h"
#include "../../ImGUI/imgui.h"
#include "../../ImGUI/imgui_internal.h"
#include "../ILayout.h"
#include "../Container/IContainer.h"

namespace Trema::View
{
    enum DockSlot
    {
        DOCK_CENTER = ImGuiDir_COUNT,
        DOCK_TOP = ImGuiDir_Up,
        DOCK_BOTTOM = ImGuiDir_Down,
        DOCK_LEFT = ImGuiDir_Left,
        DOCK_RIGHT = ImGuiDir_Right
    };

    DockSlot DockSlotFromString(const std::string& name);

    class DockSpace : public ILayout
    {
    public:
        explicit DockSpace(std::string title, ImGuiID dockspaceId);
        ~DockSpace();

        virtual void Begin();
        virtual void End();

        void Show() override;
        void AddElement(std::shared_ptr<IContainer> element, DockSlot slot);
        static std::shared_ptr<DockSpace> CreateDockSpace(std::string title, ImGuiID dockspaceId);

    protected:
        bool m_firstTime { true };
        ImGuiID m_dockspaceId;
        std::unordered_map<DockSlot, std::shared_ptr<IContainer>> m_elements;

        void ShowElements(ImGuiID dockspaceId);
    };
}

#endif //MATH4BG_DOCKSPACE_H
