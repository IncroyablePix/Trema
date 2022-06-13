//
// Created by JajaFil on 2/16/2022.
//

#include <future>
#include <sstream>
#include "TextInput.h"
#include "../../../ImGUI/imgui.h"

namespace Trema::View
{

    TextInput::TextInput(std::shared_ptr<GuiElement> parent, std::string name, std::string defaultText, size_t bufferSize) :
            GuiElement(std::move(parent), std::move(name)),
            m_bufferSize(bufferSize)
    {
        m_text.reset(new char[m_bufferSize]);
        for(int i = 0; i < m_bufferSize; i ++)
        {
            if (i == defaultText.size())
            {
                m_text.get()[i] = '\0';
                break;
            }
            else
            {
                m_text.get()[i] = defaultText[i];
            }
        }
    }

    TextInput::~TextInput() = default;

    void TextInput::Show()
    {
        BeginStyle();
        if(ImGui::InputText(NameId(), m_text.get(), m_bufferSize))
        {
            Notify();
        }
        EndStyle();
    }

    std::shared_ptr<TextInput>
    TextInput::CreateTextInput(std::shared_ptr<GuiElement> parent, std::string name, std::string defaultText,
                               size_t bufferSize)
    {
        return std::make_shared<TextInput>(std::move(parent), std::move(name), std::move(defaultText), bufferSize);
    }

    void TextInput::Notify() const
    {
        auto future = std::async(std::launch::async, [this]()
        {
            for(const auto& [name, function] : m_listeners)
            {
                std::string text { m_text.get() };
                function(std::move(text));
            }
        });
    }

    void TextInput::AddOnChangeListener(std::string name, std::function<void(std::string)> listener)
    {
        m_listeners[std::move(name)] = std::move(listener);
    }

    std::string TextInput::GetText() const
    {
        return { m_text.get() };
    }

    void TextInput::SetText(const std::string &text)
    {
        strcpy(m_text.get(), text.c_str());
    }
}