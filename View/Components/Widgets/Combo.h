//
// Created by JajaFil on 2/14/2022.
//

#ifndef TREMA_COMBO_H
#define TREMA_COMBO_H


#include "../IGuiElement.h"
#include <functional>

namespace Trema::View
{
    class Combo : public IGuiElement
    {
    public:
        Combo(std::shared_ptr<IGuiElement> parent, std::string name);
        ~Combo();
        void AddOption(std::string name, std::function<void(Combo)> listener);
        void Show() override;
        static std::shared_ptr<Combo> CreateCombo(std::shared_ptr<IGuiElement> parent, std::string name);

    private:
        std::string m_name;
        const char* m_selected {};
        std::unordered_map<std::string, std::function<void(Combo)>> m_options;
    };
}

#endif //TREMA_COMBO_H
