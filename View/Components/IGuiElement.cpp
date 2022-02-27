//
// Created by JajaFil on 2/16/2022.
//

#include "IGuiElement.h"

#include <utility>

namespace Trema::View
{
    IGuiElement::IGuiElement(std::shared_ptr<IGuiElement> parent, std::string name) :
        m_parent(std::move(parent)),
        m_name(std::move(name))
    {

    }

    const std::string &IGuiElement::GetName()
    {
        return m_name;
    }

    void IGuiElement::SetName(std::string name)
    {
        m_name = std::move(name);
    }

    const char *IGuiElement::NameId()
    {
        return m_name.c_str();
    }
}