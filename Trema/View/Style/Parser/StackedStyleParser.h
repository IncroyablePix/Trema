//
// Created by JajaFil on 3/7/2022.
//

#ifndef TREMA_STACKEDSTYLEPARSER_H
#define TREMA_STACKEDSTYLEPARSER_H


#include "IStyleParser.h"
#include "../SymbolTable.h"
#include "../Tokenizer/Tokenizer.h"
#include <stack>

namespace Trema::View
{
    class StackedStyleParser : public IStyleParser
    {
    public:
        StackedStyleParser();
        StackedStyleParser(const StackedStyleParser&) = delete;
        StackedStyleParser& operator=(const StackedStyleParser&) = delete;
        ~StackedStyleParser() override = default;
        void ParseFromCode(const std::string &code, std::vector<CompilationMistake>& mistakes) override;
        void ParseFromFile(const std::string &path, std::vector<CompilationMistake>& mistakes) override;

    private:

        unsigned int m_pos;

        void SetFromSymbolTables(const std::shared_ptr<SymbolTable>& st, const char *propName, const char* varName, std::vector<CompilationMistake>& mistakes);
        bool AssignVar(std::stack<std::unique_ptr<Token>>& tokens, const std::shared_ptr<SymbolTable>& currentSt, std::vector<CompilationMistake>& mistakes);
        void AssignProps(std::stack<std::unique_ptr<Token>>& tokens, std::shared_ptr<SymbolTable>& currentSt, std::vector<CompilationMistake>& mistakes);
        void SaveTopSymbolTable(std::string name);
        static char* CopyStr(const char* str);
    };
}

#endif //TREMA_STACKEDSTYLEPARSER_H
