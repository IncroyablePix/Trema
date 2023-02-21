#ifndef TREMA_ISTYLEPARSER_H
#define TREMA_ISTYLEPARSER_H

#include <string>
#include <unordered_map>
#include <memory>
#include "../SymbolTable.h"
#include "../CompilationMistake.h"
#include <deque>
#include <vector>

namespace Trema::View
{
    class IStyleParser
    {
    public:
        virtual ~IStyleParser() = default;
        virtual void ParseFromFile(const std::string& path) = 0;
        virtual void ParseFromCode(const std::string& code) = 0;

        inline void ClearVariables() { m_variables.clear(); }
        inline const std::unordered_map<std::string, std::shared_ptr<SymbolTable>>& GetVariables() { return m_variables; };

    protected:
        std::unordered_map<std::string, std::shared_ptr<SymbolTable>> m_variables;
        std::deque<std::shared_ptr<SymbolTable>> m_symbolTables;
    };
}

#endif //TREMA_ISTYLEPARSER_H
