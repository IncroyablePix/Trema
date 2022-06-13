//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_WINDOWCONTAINER_H
#define TREMA_WINDOWCONTAINER_H


#include "Container.h"

namespace Trema::View
{
    class WindowContainer : public Container
    {
    public:
        explicit WindowContainer(std::shared_ptr<GuiElement> parent, std::string name);
        WindowContainer(const WindowContainer&) = delete;
        WindowContainer& operator=(const WindowContainer&) = delete;
        ~WindowContainer() override;

        void Show() override;
        static std::shared_ptr<WindowContainer> CreateWindowContainer(std::shared_ptr<GuiElement> parent, std::string name);

    private:
        int GetWindowFlags();
        void ShowPureWindow();
        void ShowSubContainer() const;
        bool m_isOpened { true };
        bool m_closable { false };
    };
}

#endif //TREMA_WINDOWCONTAINER_H
