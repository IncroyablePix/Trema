//
// Created by JajaFil on 2/16/2022.
//

#ifndef TREMA_TABLE_H
#define TREMA_TABLE_H

#include <array>
#include <vector>
#include <sstream>
#include "../IGuiElement.h"
#include "../../ImGUI/imgui.h"
#include "../Container/IContainer.h"
#include "FamilyException.h"

namespace Trema::View
{
    struct TableRow : public IContainer
    {
        explicit TableRow(std::shared_ptr<IGuiElement> parent, std::string name, std::vector<std::shared_ptr<IGuiElement>> elements) :
                IContainer(std::move(parent), std::move(name)),
                Elements(std::move(elements))
        {
        }

        void AddChild(std::shared_ptr<IGuiElement> child) override
        {
            Elements.push_back(child);
        }

        std::vector<std::shared_ptr<IGuiElement>> Elements;

        void Show() override
        {
            BeginStyle();
            ImGui::TableNextRow();
            for(int i = 0; i < Elements.size(); i ++)
            {
                ImGui::TableSetColumnIndex(i);
                Elements[i]->Show();
            }
            EndStyle();
        }

        static std::shared_ptr<TableRow> CreateTableRow(std::shared_ptr<IGuiElement> parent, std::string name)
        {
            return std::make_shared<TableRow>(std::move(parent), std::move(name), std::vector<std::shared_ptr<IGuiElement>>());
        }
    };


    class Table : public IContainer
    {
    public:
        Table(std::shared_ptr<IGuiElement> parent, std::string name, std::vector<std::string> titles) :
            IContainer(std::move(parent), std::move(name)),
            m_tableColumns(titles.size()),
            m_titles(std::move(titles)),
            m_displayHeaders(true)
        {

        }

        ~Table() = default;

        void AddChild(std::shared_ptr<IGuiElement> child) override
        {
            if(IsType<TableRow>(child))
            {
                AddValue(std::dynamic_pointer_cast<TableRow>(child));
            }
            else
            {
                throw FamilyException(R"(Invalid type appended to "Table", expected "TableRow".)");
            }
        }

        void AddValue(std::shared_ptr<TableRow> row)
        {
            if(row->Elements.size() != m_tableColumns)
            {
                std::stringstream ss;
                ss << "Invalid row size [" << row->Elements.size() << "] for table size [" << m_tableColumns << "]";
                throw FamilyException(ss.str().c_str());
            }

            m_rows.push_back(std::move(row));
        }

        void Show() override
        {
            BeginStyle();
            if(ImGui::BeginTable(NameId(), (int) m_tableColumns))
            {
                for (int i = 0; i < m_tableColumns; i++)
                    ImGui::TableSetupColumn(m_titles[i].c_str());
                ImGui::TableHeadersRow();

                for(auto &tuple : m_rows)
                {
                    tuple->Show();
                }

                ImGui::EndTable();
            }
            EndStyle();
        }

        void ToggleDisplayHeaders(bool toggle)
        {
            m_displayHeaders = toggle;
        }

        static std::shared_ptr<Table> CreateTable(std::shared_ptr<IGuiElement> parent, std::string name, std::vector<std::string> titles)
        {
            return std::make_shared<Table>(std::move(parent), std::move(name), std::move(titles));
        }

    private:
        size_t m_tableColumns;
        bool m_displayHeaders;
        std::vector<std::string> m_titles;
        std::vector<std::shared_ptr<TableRow>> m_rows;
    };
}

#endif //TREMA_TABLE_H
