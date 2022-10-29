//
// Created by JajaFil on 2/18/2022.
//

#ifndef TREMA_IVIEWPARSER_H
#define TREMA_IVIEWPARSER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "../Windowing/Window.h"
#include "../Components/Layout/Docking/DockSpace.h"
#include "../Style/Parser/IStyleParser.h"
#include "../Style/CompilationMistake.h"

namespace Trema::View
{
    enum ActivityPart
    {
        APP_HEAD,
        APP_BODY,
    };

    class ViewParser
    {
    public:
        explicit ViewParser(std::unique_ptr<IStyleParser> stylesParser);
        virtual ~ViewParser() = default;
        virtual void LoadView(const std::string &path, std::shared_ptr<Window> window, Activity& activity) = 0;
        virtual void SetupWindowFromString(const std::string &code, std::shared_ptr<Window> window, Activity& activity) = 0;
        inline const std::vector<CompilationMistake>& GetMistakes() const { return m_mistakes; };

        using ElementCreator = typename std::function<std::shared_ptr<GuiElement>(std::shared_ptr<GuiElement>,
                                                                                  const std::string &,
                                                                                  std::unordered_map<std::string, std::string> &,
                                                                                  std::shared_ptr<Window>, Activity &,
                                                                                  std::string)>;

        void AddElementCreator(ActivityPart activityPart, std::string elementName, ElementCreator creator);

    protected:
        void HeadElementFromName(const std::string& elementName, const std::string& content, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window, Activity& activity);
        std::shared_ptr<GuiElement> CreateFromName(std::shared_ptr<GuiElement> parent, const std::string& elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window, Activity& activity, std::string content);
        static void TryAddLayout(const std::shared_ptr<GuiElement>& element, Activity& activity);
        static void TryAddTopMenu(const std::shared_ptr<GuiElement>& element, Activity& activity);
        static void TryAddAsChild(const std::shared_ptr<GuiElement>& container, const std::shared_ptr<GuiElement>& element, const std::string &elementName);
        void TryAddToLayout(const std::shared_ptr<GuiElement>& element, const std::shared_ptr<GuiElement> &container,
                            std::unordered_map<std::string, std::string>& attributes, Activity& activity);

        template<class T>
        inline static bool IsType(const std::shared_ptr<GuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }

    protected:
        void ApplyStyles(std::shared_ptr<Window>, Activity& activity);

        std::unique_ptr<IStyleParser> m_stylesParser;

    private:
        static int StrToInt(const std::string& str);
        static bool StrToBool(const std::string_view &str);
        static float StrToFloat(const std::string &str);
        
        std::vector<CompilationMistake> m_mistakes;
        std::unordered_map<std::string, ElementCreator> m_headElementCreators;
        std::unordered_map<std::string, ElementCreator> m_bodyElementCreators;

        unsigned long m_nameCounter { 0 };

        std::string
        GetElementName(const std::string &elementName, const std::unordered_map<std::string, std::string> &attributes,
                       std::string &content);
    };
}

#endif //TREMA_IVIEWPARSER_H
