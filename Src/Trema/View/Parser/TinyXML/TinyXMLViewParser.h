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
        TinyXMLViewParser(std::unique_ptr<IStyleParser> styleParser);
        TinyXMLViewParser(const TinyXMLViewParser&) = delete;
        TinyXMLViewParser& operator=(const TinyXMLViewParser&) = delete;
        ~TinyXMLViewParser() override = default;
        void LoadView(const std::string &path, Window* window, Activity* activity) override;
        void SetupWindowFromString(const std::string &code, Window* window, Activity* activity) override;

    private:
        void ParseDocument(TiXmlDocument& document, Window* window, Activity* activity);
        void ParseRoots(TiXmlElement* element, Window* window, Activity* activity);
        void ParseBody(TiXmlElement* body, Window* window, Activity* activity);
        void ParseHead(TiXmlElement* head, Window* window, Activity* activity);
        void ParseElement(TiXmlElement* element, const std::shared_ptr<GuiElement>& container, Window* window, Activity* activity);
        void ParseChildren(TiXmlElement *element, const std::shared_ptr<GuiElement>& container, Window* window, Activity* activity);
    };
}

#endif //TREMA_TINYXMLVIEWPARSER_H
