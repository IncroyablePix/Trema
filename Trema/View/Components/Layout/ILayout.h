//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_ILAYOUT_H
#define TREMA_ILAYOUT_H

#include "../IGuiElement.h"
#include "../Container/IContainer.h"

namespace Trema::View
{
    class IWindow;
    class ILayout : public IGuiElement
    {
    public:
        ILayout(std::string name);
        virtual void AddContainer(std::shared_ptr<IContainer> container,
                          std::unordered_map<std::string, std::string>& attributes,
                          const std::shared_ptr<IWindow>& window) = 0;
        inline void SetActiveMenuBar(bool toggle) { m_hasMenuBar = toggle; }

    protected:
        bool m_hasMenuBar;
    };
}

#endif //TREMA_ILAYOUT_H
