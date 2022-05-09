//
// Created by JajaFil on 4/3/2022.
//

#ifndef TREMA_STYLEAPPLIER_H
#define TREMA_STYLEAPPLIER_H


#include <string>
#include <unordered_map>
#include <iomanip>
#include "SymbolTable.h"
#include "../Windowing/Window.h"

namespace Trema::View
{
    class StyleApplier
    {
    public:
        void ApplyStylesToWindow(const std::unordered_map<std::string, std::shared_ptr<SymbolTable>> &vals, const std::shared_ptr<Window>& window);

    private:
        void SetGlobalStyles(const std::shared_ptr<SymbolTable>& symbolTable, const std::shared_ptr<Window> &window);
        void SetStyleForElement(const std::shared_ptr<GuiElement>& element, const std::shared_ptr<SymbolTable>& symbolTable);
        void SetStyle(ElementStyle &style, const std::shared_ptr<SymbolTable>& symbolTable);
        static char* CopyStr(const char* str);
    };
}

#endif //TREMA_STYLEAPPLIER_H
