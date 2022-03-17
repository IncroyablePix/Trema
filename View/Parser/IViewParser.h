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

namespace Trema::View
{
    class IViewParser
    {
    public:
        virtual void SetupWindowFromFile(const std::wstring &path, std::shared_ptr<IWindow> window) = 0;
        virtual void SetupWindowFromFile(const std::string &path, std::shared_ptr<IWindow> window) = 0;
        virtual void SetupWindowFromString(const std::string &code, std::shared_ptr<IWindow> window) = 0;

    protected:
        void HeadElementFromName(const std::string& elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<IWindow> window);
        std::shared_ptr<IGuiElement> CreateFromName(std::shared_ptr<IGuiElement> parent, const std::string& elementName, std::unordered_map<std::string, std::string>& attributes, std::shared_ptr<IWindow> window, std::string content);
        static void TryAddLayout(const std::shared_ptr<IGuiElement>& layout, const std::shared_ptr<IWindow>& window);
        static void TryAddAsChild(const std::shared_ptr<IGuiElement>& container, const std::shared_ptr<IGuiElement>& element, const std::string &elementName);
        void TryAddToLayout(const std::shared_ptr<IGuiElement>& element, const std::shared_ptr<IGuiElement> &container,
                            std::unordered_map<std::string, std::string>& attributes);

        template<class T>
        inline static bool IsType(const std::shared_ptr<IGuiElement> &element) { return dynamic_cast<T*>(element.get()) != nullptr; }

    private:
        static int StrToInt(const std::string& str);

        bool StrToBool(const std::string &str);
    };
}

#endif //TREMA_IVIEWPARSER_H
