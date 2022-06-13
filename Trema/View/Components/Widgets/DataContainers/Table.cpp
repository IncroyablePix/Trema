//
// Created by JajaFil on 2/16/2022.
//

#include "Table.h"

namespace Trema::View
{

    Table::Table(std::shared_ptr<GuiElement> parent, std::string name, std::vector<std::string> titles) :
            Container(std::move(parent), std::move(name)),
            m_tableColumns(titles.size()),
            m_titles(std::move(titles))
    {

    }

    void Table::AddChild(std::shared_ptr<GuiElement> child)
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

    void Table::AddValue(std::shared_ptr<TableRow> row)
    {
        if(row->Elements.size() != m_tableColumns)
        {
            std::stringstream ss;
            ss << "Invalid row size [" << row->Elements.size() << "] for table size [" << m_tableColumns << "]";
            throw FamilyException(ss.str().c_str());
        }

        m_rows.push_back(std::move(row));
    }

    void Table::Show()
    {
        BeginStyle();
        if(ImGui::BeginTable(NameId(), (int) m_tableColumns))
        {
            for (int i = 0; i < m_tableColumns; i++)
                ImGui::TableSetupColumn(m_titles[i].c_str());
            ImGui::TableHeadersRow();

            for(const auto &tuple : m_rows)
            {
                tuple->Show();
            }

            ImGui::EndTable();
        }
        EndStyle();
    }

    void Table::ToggleDisplayHeaders(bool toggle)
    {
        m_displayHeaders = toggle;
    }

    std::shared_ptr<Table>
    Table::CreateTable(std::shared_ptr<GuiElement> parent, std::string name, std::vector<std::string> titles)
    {
        return std::make_shared<Table>(std::move(parent), std::move(name), std::move(titles));
    }


}