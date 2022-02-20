//
// Created by JajaFil on 2/14/2022.
//

#ifndef TREMA_RADIO_H
#define TREMA_RADIO_H


#include <functional>
#include "../IGuiElement.h"

namespace Trema::View
{
    class Radio;
    struct RadioOption
    {
        std::string Name;
        std::function<void(Radio)> Listener;
    };

    class Radio : public IGuiElement
    {
    public:
        Radio(std::shared_ptr<IGuiElement> parent, std::string name);
        ~Radio();
        void AddOption(std::string name, std::function<void(Radio)> listener);

        void Show() override;

        static std::shared_ptr<Radio> CreateRadio(std::shared_ptr<IGuiElement> parent, std::string name);

    private:
        int m_option { 0 };
        std::vector<RadioOption> m_options;
    };
}

#endif //TREMA_RADIO_H
