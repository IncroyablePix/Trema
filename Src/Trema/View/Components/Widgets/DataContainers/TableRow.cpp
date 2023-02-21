#include "TableRow.h"

namespace Trema::View
{
    TableRow::TableRow(std::shared_ptr<GuiElement> parent, std::string name, std::vector<std::shared_ptr<GuiElement>> elements) :
    Container(std::move(parent), std::move(name)),
    Elements (std::move(elements))
    {

    }

    void TableRow::AddChild(std::shared_ptr<GuiElement> child)
    {
        Elements.push_back(std::move(child));
    }

    void TableRow::Show()
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

    std::shared_ptr<TableRow> TableRow::CreateTableRow(std::shared_ptr<GuiElement> parent, std::string name)
    {
        return std::make_shared<TableRow>(std::move(parent), std::move(name), std::vector<std::shared_ptr<GuiElement>>());
    }
}