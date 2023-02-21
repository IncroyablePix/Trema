#ifndef TREMA_PROJECT_CONTEXTMENU_H
#define TREMA_PROJECT_CONTEXTMENU_H

#include "../Container/Container.h"

namespace Trema::View
{
    class ContextMenu : public Container
    {
    public:
        ContextMenu(std::shared_ptr<GuiElement> parent, std::string name);
        ContextMenu(const ContextMenu&) = delete;
        ContextMenu& operator=(const ContextMenu&) = delete;

        ~ContextMenu() override = default;

        void Show() override;
    };
}

#endif //TREMA_PROJECT_CONTEXTMENU_H
