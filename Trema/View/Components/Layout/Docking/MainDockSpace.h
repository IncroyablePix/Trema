//
// Created by Benjam on 10/20/2021.
//

#ifndef MATH4BG_MAINDOCKSPACE_H
#define MATH4BG_MAINDOCKSPACE_H

#include "DockSpace.h"

namespace Trema::View
{
    class MainDockSpace : public DockSpace
    {
    public:
        MainDockSpace(std::string title, ImGuiID dockspaceId, bool allowSave = true);
        MainDockSpace(const MainDockSpace&) = delete;
        MainDockSpace& operator=(const MainDockSpace&) = delete;
        ~MainDockSpace() override = default;

        void Begin() override;
        void End() override;
        void Show() override;

        static std::shared_ptr<MainDockSpace> CreateMainDockSpace(std::string title, ImGuiID dockspaceId, bool saveLayout);
    };
}

#endif //MATH4BG_MAINDOCKSPACE_H
