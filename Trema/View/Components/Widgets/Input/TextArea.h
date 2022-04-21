//
// Created by JajaFil on 2/16/2022.
//

#ifndef TREMA_TEXTAREA_H
#define TREMA_TEXTAREA_H


#include "TextInput.h"

namespace Trema::View
{
    class TextArea : public TextInput
    {
    public:
        TextArea(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);
        ~TextArea();
        void Show() override;

        static std::shared_ptr<TextArea> CreateTextArea(std::shared_ptr<IGuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);
    };
}

#endif //TREMA_TEXTAREA_H
