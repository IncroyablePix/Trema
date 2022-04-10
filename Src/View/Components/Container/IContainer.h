//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_ICONTAINER_H
#define TREMA_ICONTAINER_H


#include <unordered_map>
#include <vector>
#include "../IGuiElement.h"

namespace Trema::View
{
    class IContainer : public IGuiElement
    {
    public:
        explicit IContainer(std::shared_ptr<IGuiElement> parent, std::string name);
        virtual void AddChild(std::shared_ptr<IGuiElement> child);
        inline std::vector<std::shared_ptr<IGuiElement>>& GetChildren() { return m_children; }

    protected:
        std::vector<std::shared_ptr<IGuiElement>> m_children;
    };
}


#endif //TREMA_ICONTAINER_H
