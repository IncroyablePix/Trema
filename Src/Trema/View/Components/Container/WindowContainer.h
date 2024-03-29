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
        void ShowSubContainer();
        bool m_isOpened { true };
        bool m_closable { false };

        void UpdateSize(ImVec2 &size, bool horizontal, const std::shared_ptr<GuiElement> &element) const;

        void AlignX();

        void AlignY();
    };
}

#endif //TREMA_WINDOWCONTAINER_H
