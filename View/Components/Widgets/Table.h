//
// Created by JajaFil on 2/16/2022.
//

#ifndef TREMA_TABLE_H
#define TREMA_TABLE_H

#include <array>
#include <vector>
#include "../IGuiElement.h"
#include "../../ImGUI/imgui.h"

namespace Trema::View
{
    struct TableRow : public IGuiElement
    {
        explicit TableRow(std::vector<std::shared_ptr<IGuiElement>> elements) :
                IGuiElement(nullptr, std::string("")),
                Elements(std::move(elements))
        {
        }

        std::vector<std::shared_ptr<IGuiElement>> Elements;

        void Show() override
        {
            ImGui::TableNextRow();
            for(int i = 0; i < Elements.size(); i ++)
            {
                ImGui::TableSetColumnIndex(i);
                Elements[i]->Show();
            }
        }
    };


    class Table : public IGuiElement
    {
    public:
        Table(std::shared_ptr<IGuiElement> parent, std::string name, std::vector<std::string> titles) :
            IGuiElement(std::move(parent), std::move(name)),
            m_tableColumns(titles.size()),
            m_titles(std::move(titles)),
            m_displayHeaders(true)
        {

        }
        ~Table() = default;

        void AddValue(TableRow row)
        {
            if(row.Elements.size() == m_tableColumns)
                m_rows.push_back(std::move(row));
        }

        void AddValue(std::vector<std::shared_ptr<IGuiElement>> row)
        {
            if(row.size() == m_tableColumns)
            {
                TableRow tr(std::move(row));
                m_rows.push_back(tr);
            }
        }

        void Show() override
        {
            if(ImGui::BeginTable(NameId(), (int) m_tableColumns))
            {
                for (int i = 0; i < m_tableColumns; i++)
                    ImGui::TableSetupColumn(m_titles[i].c_str());
                ImGui::TableHeadersRow();

                for(auto tuple : m_rows)
                {
                    tuple.Show();
                }

                ImGui::EndTable();
            }
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
        std::vector<TableRow> m_rows;
    };
}

#endif //TREMA_TABLE_H
