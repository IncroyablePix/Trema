//
// Created by JajaFil on 3/7/2022.
//

#ifndef TREMA_STACKEDSTYLEPARSER_H
#define TREMA_STACKEDSTYLEPARSER_H


#include "IStyleParser.h"

namespace Trema::View
{
    class StackedStyleParser : public IStyleParser
    {
    public:
        StackedStyleParser();
        void Apply(std::shared_ptr<IWindow> window) override;
        void ParseFromCode(const std::string &code) override;
        void ParseFromFile(const std::string &path) override;

    private:
        std::vector<std::string> m_tokens;
        unsigned int m_pos;
    };
}

#endif //TREMA_STACKEDSTYLEPARSER_H
