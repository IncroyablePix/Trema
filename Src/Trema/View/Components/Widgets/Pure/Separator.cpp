//
// Created by JajaFil on 3/28/2022.
//

#include "Separator.h"

#include <utility>

namespace Trema::View
{

    Separator::Separator(std::shared_ptr<GuiElement> parent, std::string name) :
            GuiElement(std::move(parent), std::move(name))
    {

    }

    Separator::~Separator()
    {

    }

    void Separator::Show()
    {
        ImGui::Separator();
    }

    std::shared_ptr<Separator> Separator::CreateSeparator(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<Separator>(std::move(parent), std::move(name));
    }
}