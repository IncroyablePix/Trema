//
// Created by JajaFil on 2/16/2022.
//

#ifndef TREMA_TEXTINPUT_H
#define TREMA_TEXTINPUT_H

#include "../../IGuiElement.h"
#include <unordered_map>
#include <functional>

namespace Trema::View
{
    class TextInput : public IGuiElement
    {
    public:
        TextInput(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);
        virtual ~TextInput();
        const std::string & GetText();
        void Show() override;
        void AddOnChangeListener(std::string name, std::function<void(std::string text)> listener);

        static std::shared_ptr<TextInput> CreateTextInput(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);

    protected:
        static const size_t defaultBufferSize = 256;
        size_t m_bufferSize;
        char* m_text;

        std::unordered_map<std::string, std::function<void(std::string text)>> m_listeners;

        void Notify();
    };
}

#endif //TREMA_TEXTINPUT_H
