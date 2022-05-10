//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_ILAYOUT_H
#define TREMA_ILAYOUT_H

#include "../GuiElement.h"
#include "../Container/Container.h"

namespace Trema::View
{
    class Window;
    class Layout : public GuiElement
    {
    public:
        Layout(std::string name);
        virtual void AddContainer(std::shared_ptr<Container> container,
                          std::unordered_map<std::string, std::string>& attributes,
                          const std::shared_ptr<Window>& window) = 0;
        inline void SetActiveMenuBar(bool toggle) { m_hasMenuBar = toggle; }

    protected:
        bool m_hasMenuBar;
    };
}

#endif //TREMA_ILAYOUT_H
