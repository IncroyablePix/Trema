//
// Created by JajaFil on 6/13/2022.
//

#ifndef TREMA_PROJECT_TABLEROW_H
#define TREMA_PROJECT_TABLEROW_H

#include "../../Container/Container.h"
#include <memory>

namespace Trema::View
{
    struct TableRow : public Container
    {
        TableRow(std::shared_ptr<GuiElement> parent, std::string name, std::vector<std::shared_ptr<GuiElement>> elements);
        void AddChild(std::shared_ptr<GuiElement> child) override;
        void Show() override;

        std::vector<std::shared_ptr<GuiElement>> Elements;

        static std::shared_ptr<TableRow> CreateTableRow(std::shared_ptr<GuiElement> parent, std::string name);
    };
}

#endif //TREMA_PROJECT_TABLEROW_H
