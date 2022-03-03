//
// Created by JajaFil on 2/16/2022.
//

#include <future>
#include <sstream>
#include "TextInput.h"
#include "../../../ImGUI/imgui.h"

namespace Trema::View
{

    TextInput::TextInput(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText, size_t bufferSize) :
            IGuiElement(std::move(parent), std::move(name)),
//            m_text(defaultText.c_str()),
            m_bufferSize(bufferSize)
    {
        m_text = new char[m_bufferSize];
        for(int i = 0; i < m_bufferSize; i ++)
        {
            if (i == defaultText.size())
            {
                m_text[i] = '\0';
                break;
            }
            else
            {
                m_text[i] = defaultText[i];
            }
        }
    }

    TextInput::~TextInput()
    {
        delete[] m_text;
    }

    void TextInput::Show()
    {
        if(ImGui::InputText(NameId(), m_text, m_bufferSize))
        {
            Notify();
        }
    }

    std::shared_ptr<TextInput>
    TextInput::CreateTextInput(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText,
                               size_t bufferSize)
    {
        return std::make_shared<TextInput>(std::move(parent), std::move(name), std::move(defaultText), bufferSize);
    }

    void TextInput::Notify()
    {
        auto future = std::async(std::launch::async, [this]()
        {
            for(const auto& [name, function] : m_listeners)
            {
                std::string text { m_text };
                function(std::move(text));
            }
        });
    }

    void TextInput::AddOnChangeListener(std::string name, std::function<void(std::string)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    std::string TextInput::GetText()
    {
        return { m_text };
    }

    void TextInput::SetText(const std::string &text)
    {
        strcpy(m_text, text.c_str());
    }
}