//
// Created by JajaFil on 2/18/2022.
//

#ifndef TREMA_TINYXMLVIEWPARSER_H
#define TREMA_TINYXMLVIEWPARSER_H

#include "../IViewParser.h"
#include "tinyxml.h"

namespace Trema::View
{
    class TinyXMLViewParser : public IViewParser
    {
    public:
        void SetupWindowFromFile(const std::string &path, std::shared_ptr<IWindow> window) override;
        void SetupWindowFromFile(const std::wstring &path, std::shared_ptr<IWindow> window) override;
        void SetupWindowFromString(const std::string &code, std::shared_ptr<IWindow> window) override;

    private:
        void ParseDocument(TiXmlDocument& document, std::shared_ptr<IWindow> window);
        void ParseElement(TiXmlElement* element, const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<IWindow>& window);
        void ParseChildren(TiXmlElement *element, const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<IWindow>& window);
    };
}

#endif //TREMA_TINYXMLVIEWPARSER_H
