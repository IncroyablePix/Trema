//
// Created by JajaFil on 2/16/2022.
//

#ifndef TREMA_TABLE_H
#define TREMA_TABLE_H

#include <array>
#include <vector>
#include <sstream>
#include "../../GuiElement.h"
#include "../../../ImGUI/imgui.h"
#include "../../Container/Container.h"
#include "../FamilyException.h"
#include "TableRow.h"

namespace Trema::View
{
    class Table : public Container
    {
    public:
        Table(std::shared_ptr<GuiElement> parent, std::string name, std::vector<std::string> titles);

        Table(const Table&) = delete;
        Table& operator=(const Table&) = delete;
        ~Table() override = default;

        void AddChild(std::shared_ptr<GuiElement> child) override;
        void AddValue(std::shared_ptr<TableRow> row);

        void Show() override;

        void ToggleDisplayHeaders(bool toggle);

        static std::shared_ptr<Table> CreateTable(std::shared_ptr<GuiElement> parent, std::string name, std::vector<std::string> titles);

    private:
        size_t m_tableColumns;
        bool m_displayHeaders { true };
        std::vector<std::string> m_titles;
        std::vector<std::shared_ptr<TableRow>> m_rows;
    };
}

#endif //TREMA_TABLE_H
