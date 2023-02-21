#include <iterator>
#include <utility>
#include <vector>
#include <iostream>
#include "ViewParser.h"
#include "../Components/Widgets/Button.h"
#include "../Exceptions/ParsingException.h"
#include "../Components/Layout/LayoutException.h"
#include "../Style/StyleApplier.h"
#include "../Components/Widgets/Sliders/SliderFloat.h"
#include "../Activities/Activity.h"
#include "TremaStandardElementsLibrary.h"

namespace Trema::View
{
    ViewParser::ViewParser(std::unique_ptr<IStyleParser> stylesParser, MistakesContainer& mistakes) :
        m_stylesParser(std::move(stylesParser)),
        m_mistakes(mistakes)
    {
        TremaStandardElementsLibrary lib;
        lib.AddElements(*this);
    }

    void ViewParser::ApplyStyles(std::shared_ptr<Window> window, Activity& activity)
    {
        auto vals = m_stylesParser->GetVariables();
        StyleApplier applier;

        window->Build();
        applier.ApplyStylesToWindow(vals, activity);
    }

    void ViewParser::HeadElementFromName(const std::string& elementName, const std::string& content, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window, Activity& activity)
    {
        auto name = attributes["name"];

        std::string elementNameUpper = elementName;
        std::ranges::transform(elementNameUpper.begin(), elementNameUpper.end(), elementNameUpper.begin(), ::toupper);

        if (m_headElementCreators.contains(elementNameUpper))
        {
            auto function = m_headElementCreators[elementNameUpper];
            function(name, attributes, std::move(window),activity, *m_stylesParser, content);
        }
        else
        {
            m_mistakes << CompilationMistake { .Line = 1, .Position = 0, .Code = ErrorCode::ElementNotFound, .Extra = elementName };
        }
    }

    std::string ViewParser::GetElementName(const std::string &elementName, const std::unordered_map<std::string, std::string> &attributes, std::string& content)
    {
        if(attributes.contains("name"))
            return attributes.at("name");

        if(!content.empty())
            return content;

        std::stringstream ss;
        ss << "##" << elementName << (++m_nameCounter);

        return ss.str();
    }

    std::shared_ptr<GuiElement> ViewParser::CreateFromName(std::shared_ptr<GuiElement> parent,
                                                           const std::string &elementName,
                                                           std::unordered_map<std::string, std::string>& attributes,
                                                           std::shared_ptr<Window> window,
                                                           Activity& activity, std::string content)
    {
        auto name = std::move(GetElementName(elementName, attributes, content));
        auto id = !attributes.contains("id") ? "" : attributes["id"];

        //---

        std::string elementNameUpper = elementName;
        std::ranges::transform(elementNameUpper.begin(), elementNameUpper.end(), elementNameUpper.begin(), ::toupper);

        if (m_bodyElementCreators.contains(elementNameUpper))
        {
            auto function = m_bodyElementCreators[elementNameUpper];
            auto element = function(std::move(parent), name, attributes, std::move(window), activity, content);

            if(!id.empty())
                activity.AddElementId(id, element);

            return element;
        }
        else
        {
            return nullptr;
        }
    }

    void ViewParser::TryAddLayout(const std::shared_ptr<GuiElement>& element, Activity& activity)
    {
        if(IsType<Layout>(element))
        {
            std::shared_ptr<Layout> newLayout = std::dynamic_pointer_cast<Layout>(element);
            activity.SetLayout(newLayout);
        }
        else
        {
            throw ParsingException("Root element should be layout");
        }
    }

    void ViewParser::TryAddAsChild(const std::shared_ptr<GuiElement> &container, const std::shared_ptr<GuiElement> &element, const std::string &elementName)
    {
        if (auto* c = dynamic_cast<Container*>(container.get()))
        {
            c->AddChild(element);
        }
        else
        {
            std::stringstream ss;
            ss << "Tried to append to non container element: [" << elementName <<  "]";
            throw ParsingException(ss.str().c_str());
        }
    }

    void ViewParser::TryAddToLayout(const std::shared_ptr<GuiElement>& element,
                                    const std::shared_ptr<GuiElement> &container,
                                    std::unordered_map<std::string, std::string>& attributes,
                                    Activity& activity)
    {
        if(dynamic_cast<Container*>(element.get()) == nullptr)
            throw ParsingException("Only Container can fit into layout");

        std::shared_ptr<Container> newContainer = std::dynamic_pointer_cast<Container>(element);

        if(auto* layout = dynamic_cast<Layout*>(container.get()))
        {
            if(IsType<TopMenu>(element))
            {
                auto menu = std::dynamic_pointer_cast<TopMenu>(newContainer);
                activity.SetTopMenu(menu);
                return;
            }

            try
            {
                layout->AddContainer(newContainer, attributes);
            }
            catch(const LayoutException& e)
            {
                throw ParsingException(e.what());
            }
        }
        else
        {
            throw ParsingException("Tried to append container to non-layout element");
        }
    }

    void ViewParser::TryAddTopMenu(const std::shared_ptr<GuiElement> &element, Activity& activity)
    {
        if(IsType<TopMenu>(element))
        {
            std::shared_ptr<TopMenu> newMenu = std::dynamic_pointer_cast<TopMenu>(element);
            activity.SetTopMenu(newMenu);
        }
        else
        {
            throw ParsingException("Type mismatch to top menu item!");
        }
    }

    void ViewParser::AddHeadElementCreator(std::string elementName, ViewParser::HeadElementCreator creator)
    {
        m_headElementCreators[std::move(elementName)] = std::move(creator);
    }

    void ViewParser::AddBodyElementCreator(std::string elementName, ViewParser::BodyElementCreator creator)
    {
        m_bodyElementCreators[std::move(elementName)] = std::move(creator);
    }
}