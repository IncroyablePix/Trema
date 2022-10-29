//
// Created by Benjam on 10/13/2022.
//

#ifndef TREMA_PROJECT_VECTORVIEW_H
#define TREMA_PROJECT_VECTORVIEW_H

#include <vector>
#include <string>
#include "../../../../Observable/Collections/ObservableCollection.h"
#include "../../GuiElement.h"

namespace Trema::View
{
    class VectorView : public GuiElement
    {
    public:
        VectorView(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<Observable::ObservableCollection<std::vector<std::string>>> collection);
        ~VectorView();
        void Show() override;

        static std::shared_ptr<VectorView> CreateVectorView(std::shared_ptr<GuiElement> parent, std::string name, std::shared_ptr<Observable::ObservableCollection<std::vector<std::string>>> collection);
    private:
        std::shared_ptr<Observable::ObservableCollection<std::vector<std::string>>> m_collection;
    };

} // Trema

#endif //TREMA_PROJECT_VECTORVIEW_H
