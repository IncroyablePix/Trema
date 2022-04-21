//
// Created by JajaFil on 2/16/2022.
//

#include "TextArea.h"
#include "../../../ImGUI/imgui.h"

#include <utility>

namespace Trema::View
{

    TextArea::TextArea(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText,
                       size_t bufferSize) : TextInput(std::move(parent), std::move(name), std::move(defaultText), bufferSize)
    {

    }

    TextArea::~TextArea()
    {

    }

    void TextArea::Show()
    {
        BeginStyle();
        ImGui::InputTextMultiline(NameId(), m_text, m_bufferSize);
        EndStyle();
    }

    std::shared_ptr<TextArea> TextArea::CreateTextArea(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText,
                             size_t bufferSize)
    {
        return std::make_shared<TextArea>(std::move(parent), std::move(name), std::move(defaultText), bufferSize);
    }
}