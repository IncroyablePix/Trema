//
// Created by JajaFil on 2/18/2022.
//

#ifndef TREMA_IVIEWPARSER_H
#define TREMA_IVIEWPARSER_H

#include <string>
#include <memory>
#include <vector>
#include <unordered_map>
#include "../IWindow.h"
#include "../Components/Layout/Docking/DockSpace.h"
#include "../Style/IStyleParser.h"
#include "../Style/CompilationMistake.h"

namespace Trema::View
{
    class IViewParser
    {
    public:
        explicit IViewParser(std::unique_ptr<IStyleParser> stylesParser);
        virtual void SetupWindowFromFile(const std::wstring &path, std::shared_ptr<IWindow> window) = 0;
        virtual void SetupWindowFromFile(const std::string &path, std::shared_ptr<IWindow> window) = 0;
        virtual void SetupWindowFromString(const std::string &code, std::shared_ptr<IWindow> window) = 0;
        inline const std::vector<CompilationMistake>& GetMistakes() const { return m_mistakes; };

    protected:
        void HeadElementFromName(const std::string& elementName, const std::string& content, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<IWindow> window);
        std::shared_ptr<IGuiElement> CreateFromName(std::shared_ptr<IGuiElement> parent, const std::string& elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<IWindow> window, std::string content);
        static void TryAddLayout(const std::shared_ptr<IGuiElement>& element, const std::shared_ptr<IWindow>& window);
        static void TryAddTopMenu(const std::shared_ptr<IGuiElement>& element, const std::shared_ptr<IWindow>& window);
        static void TryAddAsChild(const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<IGuiElement>& element, const std::string &elementName);
        void TryAddToLayout(const std::shared_ptr<IGuiElement>& element, const std::shared_ptr<IGuiElement> &container,
                            std::unordered_map<std::string, std::string>& attributes, const std::shared_ptr<IWindow>& window);

        template<class T>
        inline static bool IsType(const std::shared_ptr<IGuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }
    protected:
        void ApplyStyles(const std::shared_ptr<IWindow>& window);

        std::unique_ptr<IStyleParser> m_stylesParser;

    private:
        static int StrToInt(const std::string& str);
        bool StrToBool(const std::string &str);
        std::vector<CompilationMistake> m_mistakes;
    };
}

#endif //TREMA_IVIEWPARSER_H