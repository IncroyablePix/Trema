//
// Created by JajaFil on 2/15/2022.
//

#ifndef TREMA_TEXT_H
#define TREMA_TEXT_H

#include "../../GuiElement.h"

namespace Trema::View
{
    class Text : public GuiElement
    {
    public:
        Text(std::shared_ptr<GuiElement> parent, std::string name, bool wrapped = true);
        ~Text();
        void Show() override;
        const std::string & GetName() override;
        void SetWrapped(bool wrapped);
        bool GetWrapped() const;

        static std::shared_ptr<Text> CreateText(std::shared_ptr<GuiElement> parent, std::string name, bool wrapped = false);

    private:
        bool m_wrapped { true };
    };
}

#endif //TREMA_TEXT_H
