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
#include "../Style/StyleApplier.h"
#include "../Style/MistakesContainer.h"

namespace Trema::View
{
    class ViewParser
    {
    public:
        explicit ViewParser(std::unique_ptr<IStyleParser> stylesParser, MistakesContainer& mistakes);
        virtual ~ViewParser() = default;
        virtual void LoadView(const std::string &path, std::shared_ptr<Window> window, Activity& activity) = 0;
        virtual void SetupWindowFromString(const std::string &code, std::shared_ptr<Window> window, Activity& activity) = 0;
        inline const MistakesContainer& GetMistakes() const { return m_mistakes; };

        using BodyElementCreator = typename std::function<std::shared_ptr<GuiElement>(
                std::shared_ptr<GuiElement> parent,
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                std::string content)>;

        using HeadElementCreator = typename std::function<void(
                std::string name,
                std::unordered_map<std::string, std::string> &attributes,
                std::shared_ptr<Window> window,
                Activity &activity,
                IStyleParser& styleApplier,
                std::string content)>;

        void AddHeadElementCreator(std::string elementName, HeadElementCreator creator);
        void AddBodyElementCreator(std::string elementName, BodyElementCreator creator);

    protected:
        void HeadElementFromName(const std::string& elementName, const std::string& content, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window, Activity& activity);
        std::shared_ptr<GuiElement> CreateFromName(std::shared_ptr<GuiElement> parent, const std::string& elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<Window> window, Activity& activity, std::string content);
        static void TryAddLayout(const std::shared_ptr<GuiElement>& element, Activity& activity);
        static void TryAddTopMenu(const std::shared_ptr<GuiElement>& element, Activity& activity);
        static void TryAddAsChild(const std::shared_ptr<GuiElement>& container, const std::shared_ptr<GuiElement>& element, const std::string &elementName);
        void TryAddToLayout(const std::shared_ptr<GuiElement>& element, const std::shared_ptr<GuiElement> &container,
                            std::unordered_map<std::string, std::string>& attributes, Activity& activity);
        void ApplyStyles(std::shared_ptr<Window>, Activity& activity);

        template<class T>
        inline static bool IsType(const std::shared_ptr<GuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }

        MistakesContainer& m_mistakes;
        std::unique_ptr<IStyleParser> m_stylesParser;

    private:
        std::unordered_map<std::string, HeadElementCreator> m_headElementCreators;
        std::unordered_map<std::string, BodyElementCreator> m_bodyElementCreators;

        unsigned long m_nameCounter { 0 };

        std::string
        GetElementName(const std::string &elementName, const std::unordered_map<std::string, std::string> &attributes,
                       std::string &content);
    };
}

#endif //TREMA_IVIEWPARSER_H
