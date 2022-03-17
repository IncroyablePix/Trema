//
// Created by JajaFil on 3/7/2022.
//

#ifndef TREMA_ISTYLEPARSER_H
#define TREMA_ISTYLEPARSER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "../IWindow.h"


namespace Trema::View
{
    enum ObjectType
    {
        GlobalStyle,
        IdStyle
    };

    struct AbstractStyle
    {
        ObjectType Type;
        std::string Identifier;
    };

    class IStyleParser
    {
    public:
        virtual void Apply(std::shared_ptr<IWindow> window) = 0;
        virtual void ParseFromFile(const std::string& path) = 0;
        virtual void ParseFromCode(const std::string& code) = 0;

    protected:
        std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_styles;
    };
}

#endif //TREMA_ISTYLEPARSER_H
