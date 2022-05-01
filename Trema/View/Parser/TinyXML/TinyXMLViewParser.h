//
// Created by JajaFil on 2/18/2022.
//

#ifndef TREMA_TINYXMLVIEWPARSER_H
#define TREMA_TINYXMLVIEWPARSER_H

#include "../ViewParser.h"
#include "tinyxml.h"
#include "../../Style/Parser/IStyleParser.h"

namespace Trema::View
{
    class TinyXMLViewParser : public ViewParser
    {
    public:
        explicit TinyXMLViewParser(std::unique_ptr<IStyleParser> styleParser);
        void SetupWindowFromFile(const std::string &path, std::shared_ptr<Window> window) override;
        void SetupWindowFromFile(const std::wstring &path, std::shared_ptr<Window> window) override;
        void SetupWindowFromString(const std::string &code, std::shared_ptr<Window> window) override;

    private:
        void ParseDocument(TiXmlDocument& document, std::shared_ptr<Window> window);
        void ParseRoots(TiXmlElement* element, const std::shared_ptr<Window>& window);
        void ParseBody(TiXmlElement* body, const std::shared_ptr<Window>& window);
        void ParseHead(TiXmlElement* head, const std::shared_ptr<Window>& window);
        void ParseElement(TiXmlElement* element, const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<Window>& window);
        void ParseChildren(TiXmlElement *element, const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<Window>& window);
    };
}

#endif //TREMA_TINYXMLVIEWPARSER_H
