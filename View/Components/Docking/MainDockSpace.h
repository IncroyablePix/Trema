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
        MainDockSpace(std::string title, ImGuiID dockspaceId);
        void Begin() override;
        void End() override;
        ~MainDockSpace();
        void Show() override;

        static std::shared_ptr<MainDockSpace> CreateMainDockSpace(std::string title, ImGuiID dockspaceId);
    };
}

#endif //MATH4BG_MAINDOCKSPACE_H
