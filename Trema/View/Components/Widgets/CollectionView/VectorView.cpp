//
// Created by Benjam on 10/13/2022.
//

#include "VectorView.h"

namespace Trema::View
{
    VectorView::VectorView(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<Observable::ObservableCollection<std::vector<std::string>>> collection) :
            GuiElement(std::move(parent), std::move(name)),
            m_collection(std::move(collection))
    {
        m_collection->Subscribe(NameId(), [this](const Observable::ObservableCollection<std::vector<std::string>>& collection)
        {
            // std::cout << "Collection changed" << std::endl;
        });
    }

    VectorView::~VectorView() = default;

    void VectorView::Show()
    {
        bool first = true;
        for(const auto& val : m_collection->GetContainer())
        {
            if(first)
                first = false;
            else
                m_parent->AlignX();

            BeginStyle();
            AlignX();
            ImGui::Text(val.c_str());
            EndStyle();
        }
    }

    std::shared_ptr<VectorView> VectorView::CreateVectorView(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<Observable::ObservableCollection<std::vector<std::string>>> collection)
    {
        return std::make_shared<VectorView>(std::move(parent), std::move(name), std::move(collection));
    }
} // Trema