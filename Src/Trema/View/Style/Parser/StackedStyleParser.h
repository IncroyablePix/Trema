//
// Created by JajaFil on 3/7/2022.
//

#ifndef TREMA_STACKEDSTYLEPARSER_H
#define TREMA_STACKEDSTYLEPARSER_H


#include "IStyleParser.h"
#include "../SymbolTable.h"
#include "../Tokenizer/Tokenizer.h"
#include "OperationsTable.h"
#include <stack>

namespace Trema::View
{
    class StackedStyleParser : public IStyleParser
    {
    public:
        StackedStyleParser(MistakesContainer& mistakes);
        StackedStyleParser(const StackedStyleParser&) = delete;
        StackedStyleParser& operator=(const StackedStyleParser&) = delete;
        ~StackedStyleParser() override = default;
        void ParseFromCode(const std::string &code) override;
        void ParseFromFile(const std::string &path) override;

    private:
        unsigned int m_pos;
        OperationsTable m_operationsTable;
        MistakesContainer& m_mistakes;

        void SetFromSymbolTables(const std::shared_ptr<SymbolTable>& st, const char *propName, const char* varName);
        bool ProcessOperators(std::stack<std::unique_ptr<Token>>& operators, std::unique_ptr<Token>& currentOperator, std::stack<std::unique_ptr<Token>>& tokens);
        bool AssignVar(std::stack<std::unique_ptr<Token>>& tokens, std::stack<std::unique_ptr<Token>>& operators, const std::shared_ptr<SymbolTable>& currentSt);
        void AssignProps(std::stack<std::unique_ptr<Token>>& tokens, std::shared_ptr<SymbolTable>& currentSt);
        void SaveTopSymbolTable(std::string name);
        static char* CopyStr(const char* str);

        std::any GetNextTokenValue(std::stack<std::unique_ptr<Token>> &tokens) const;
    };
}

#endif //TREMA_STACKEDSTYLEPARSER_H
