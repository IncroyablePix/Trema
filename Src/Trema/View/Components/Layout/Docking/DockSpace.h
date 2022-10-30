//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_DOCKSPACE_H
#define MATH4BG_DOCKSPACE_H

#include <string>
#include <array>
#include <memory>
#include <unordered_map>
#include "../../GuiElement.h"
#include <imgui.h>
#include <imgui_internal.h>
#include "../Layout.h"
#include "../../Container/Container.h"

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

    DockSlot DockSlotFromString(const std::string_view &name);

    class DockSpace : public Layout
    {
    public:
        explicit DockSpace(std::string title, bool allowSave);
        DockSpace(const DockSpace&) = delete;
        DockSpace& operator=(const DockSpace&) = delete;

        virtual void Begin();
        virtual void End();
        void AddContainer(std::shared_ptr<Container> container, std::unordered_map<std::string, std::string> &attributes) override;

        void Show() override;
        void AddElement(std::shared_ptr<Container> element, DockSlot slot);
        static std::shared_ptr<DockSpace> CreateDockSpace(std::string title, ImGuiID dockspaceId);

    protected:
        void ShowElements(ImGuiID dockspaceId) const;
        bool IsSavedDock() const;

        std::unordered_map<DockSlot, std::shared_ptr<Container>> m_elements;
        bool m_firstTime { true };
        bool m_allowSave { true };
    };
}

#endif
