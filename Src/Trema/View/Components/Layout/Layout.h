#ifndef TREMA_ILAYOUT_H
#define TREMA_ILAYOUT_H

#include "../GuiElement.h"
#include "../Container/Container.h"

namespace Trema::View
{
    class Layout : public GuiElement
    {
    public:
        Layout(std::string name);
        ~Layout() override = default;
        virtual void AddContainer(std::shared_ptr<Container> container,
                          std::unordered_map<std::string, std::string>& attributes) = 0;
        inline void SetActiveMenuBar(bool toggle) { m_hasMenuBar = toggle; }

    protected:
        bool m_hasMenuBar { false };
    };
}

#endif //TREMA_ILAYOUT_H
