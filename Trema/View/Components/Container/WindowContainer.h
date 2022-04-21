//
// Created by JajaFil on 2/13/2022.
//

#ifndef TREMA_WINDOWCONTAINER_H
#define TREMA_WINDOWCONTAINER_H


#include "IContainer.h"

namespace Trema::View
{
    class WindowContainer : public IContainer
    {
    public:
        explicit WindowContainer(std::shared_ptr<IGuiElement> parent, std::string name);
        ~WindowContainer();

        void Show() override;
        static std::shared_ptr<WindowContainer> CreateWindowContainer(std::shared_ptr<IGuiElement> parent, std::string name);

    private:
        int GetWindowFlags();
        void ShowPureWindow();
        void ShowSubContainer();
        bool m_isOpened { true };
        bool m_closable { false };
    };
}

#endif //TREMA_WINDOWCONTAINER_H
