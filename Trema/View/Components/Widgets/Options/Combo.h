//
// Created by JajaFil on 2/14/2022.
//

#ifndef TREMA_COMBO_H
#define TREMA_COMBO_H


#include "../../GuiElement.h"
#include "../../Container/Container.h"
#include <functional>

namespace Trema::View
{
    class Combo : public Container
    {
    public:
        Combo(std::shared_ptr<GuiElement> parent, std::string name);
        ~Combo();
        void AddChild(std::shared_ptr<GuiElement> child) override;
        void AddOption(std::string name);
        void AddOnClickListener(std::string name, std::function<void(const std::string&)> listener);
        void Show() override;

        inline void SetOption(const char* selected) { m_selected = selected; }
        inline std::string GetOption() const { return m_selected; }
        static std::shared_ptr<Combo> CreateCombo(std::shared_ptr<GuiElement> parent, std::string name);

    private:
        std::string m_name;
        const char* m_selected {};
        std::vector<std::string> m_options;
        std::unordered_map<std::string, std::function<void(const std::string& option)>> m_listeners;
    };
}

#endif //TREMA_COMBO_H
