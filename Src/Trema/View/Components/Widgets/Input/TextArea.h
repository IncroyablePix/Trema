#ifndef TREMA_TEXTAREA_H
#define TREMA_TEXTAREA_H


#include "TextInput.h"

namespace Trema::View
{
    class TextArea : public TextInput
    {
    public:
        TextArea(std::shared_ptr<GuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);
        TextArea(const TextArea&) = delete;
        TextArea& operator=(const TextArea&) = delete;
        ~TextArea() override;
        void Show() override;

        static std::shared_ptr<TextArea> CreateTextArea(std::shared_ptr<GuiElement> parent, std::string name, std::string defaultText = "", size_t bufferSize = defaultBufferSize);
    };
}

#endif //TREMA_TEXTAREA_H
