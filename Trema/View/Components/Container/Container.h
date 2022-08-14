//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_ICONTAINER_H
#define TREMA_ICONTAINER_H


#include <unordered_map>
#include <vector>
#include "../GuiElement.h"

namespace Trema::View
{
    class Container : public GuiElement
    {
    public:
        Container(std::shared_ptr<GuiElement> parent, std::string name);
        Container(const Container&) = delete;
        Container& operator=(const Container&) = delete;

        ~Container() override = default;

        virtual void AddChild(std::shared_ptr<GuiElement> child);
        inline std::vector<std::shared_ptr<GuiElement>>& GetChildren() { return m_children; }

        inline static void ToggleSubContainerization(bool toggle) { SubContainer = toggle; }

    protected:
        std::vector<std::shared_ptr<GuiElement>> m_children;
        static bool SubContainer;
    };
}


#endif //TREMA_ICONTAINER_H
