//
// Created by JajaFil on 2/16/2022.
//

#ifndef TREMA_TEXTINPUT_H
#define TREMA_TEXTINPUT_H

#include "../../GuiElement.h"
#include <unordered_map>
#include <functional>

namespace Trema::View
{
    class TextInput : public GuiElement
    {
    public:
        TextInput(std::shared_ptr<GuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);
        TextInput(const TextInput&) = delete;
        TextInput& operator=(const TextInput&) = delete;
        virtual ~TextInput();
        std::string GetText() const;
        void SetText(const std::string& text);
        void Show() override;
        void AddOnChangeListener(std::string name, std::function<void(std::string text)> listener);

        static std::shared_ptr<TextInput> CreateTextInput(std::shared_ptr<GuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);

    protected:
        static const size_t defaultBufferSize = 256;
        size_t m_bufferSize;
        std::unique_ptr<char> m_text;

        std::unordered_map<std::string, std::function<void(std::string text)>> m_listeners;

        void Notify() const;
    };
}

#endif //TREMA_TEXTINPUT_H
