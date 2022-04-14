//
// Created by JajaFil on 3/7/2022.
//

#include <fstream>
#include <stack>
#include <iostream>
#include "StackedStyleParser.h"
#include "../Exceptions/FileNotFoundException.h"
#include "../Exceptions/ParsingException.h"

namespace Trema::View
{
    StackedStyleParser::StackedStyleParser()
    {

    }

    void StackedStyleParser::ParseFromCode(const std::string &code, std::vector<CompilationMistake>& mistakes)
    {
        Tokenizer tokenizer(code, mistakes);
        //Tokenizer tokenizer("", mistakes);
        if(tokenizer.Empty())
            return;

        std::stack<std::unique_ptr<Token>> tokens;

        auto currentSt = std::make_shared<SymbolTable>();
        m_symbolTables.push_back(currentSt);

        auto currentToken = tokenizer.GetNextToken();
        while(!tokenizer.Empty() && currentToken->GetTokenType() != T_STOP)
        {
            std::cout << currentToken->GetIdentity();
            switch(currentToken->GetTokenType())
            {
                case T_IDENTITY:
                case T_IDENTIFIER:
                case T_LBOOL:
                case T_LNUMBER:
                case T_LFNUMBER:
                case T_LSTRING:
                case T_PROPASSIGN:
                case T_VARASSIGN:
                    tokens.push(std::move(currentToken));
                    break;
                case T_LCURLY:
                    currentSt = std::make_shared<SymbolTable>();
                    m_symbolTables.push_back(currentSt);
                    tokens.push(std::move(currentToken));
                    break;
                case T_RCURLY:
                    AssignProps(tokens, currentSt, mistakes);
                    break;

                case T_ENDINS:
                    if(!AssignVar(tokens, currentSt, mistakes))
                    {
                        mistakes.emplace_back(CompilationMistake { .Line = currentToken->GetLine(), .Position = currentToken->GetPosition(), .Code = ErrorCode::UnexpectedToken, .Extra = ";" });
                    }
                    break;

                case T_LPAR:
                case T_RPAR:
                case T_STOP:
                    break;
            }

            currentToken = tokenizer.GetNextToken();
        }

        SaveTopSymbolTable("*");

        /*for(const auto& [name, st] : m_variables)
        {
            std::cout << name << ":\n" << *st;
        }

        std::cout << std::flush;*/
    }

    void StackedStyleParser::ParseFromFile(const std::string &path, std::vector<CompilationMistake>& mistakes)
    {
        std::fstream file;
        file.open(path, std::ios::in);

        if(!file.is_open())
        {
            std::stringstream message;
            message << "File not found: " << path;
            throw FileNotFoundException(message.str().c_str());
        }

        std::stringstream code;
        std::string line;
        while(std::getline(file, line))
        {
            code << line << "\n";
        }

        file.close();

        ParseFromCode(code.str(), mistakes);
    }

    void StackedStyleParser::SetFromSymbolTables(const std::shared_ptr<SymbolTable>& symbolTable, const char *propName, const char *varName, std::vector<CompilationMistake>& mistakes)
    {
        for(const auto& st : m_symbolTables)
        {
            if(st->HasVariable(varName))
            {
                auto v = st->GetVariable(varName);
                switch(v->GetType())
                {
                    case TYPE_NUM:
                        symbolTable->SetVariable<int64_t>(propName, (int64_t*)v->CopyValue());
                        return;
                    case TYPE_FLOAT:
                        symbolTable->SetVariable<double>(propName, (double*)v->CopyValue());
                        return;
                    case TYPE_STR:
                        symbolTable->SetVariable<char>(propName, (char*)v->CopyValue());
                        return;
                    case TYPE_BOOL:
                        symbolTable->SetVariable<bool>(propName, (bool*)v->CopyValue());
                        return;
                }
            }
        }

        mistakes.emplace_back(CompilationMistake { .Line = 1, .Position = 0, .Code = ErrorCode::UndefinedSymbol, .Extra = std::string(varName) });
    }

    bool StackedStyleParser::AssignVar(std::stack<std::unique_ptr<Token>>& tokens, const std::shared_ptr<SymbolTable>& currentSt, std::vector<CompilationMistake>& mistakes)
    {
        if (tokens.size() < 3)
//            throw ParsingException(R"(Unexpected symbol ";")");
            return false;

        auto val = std::move(tokens.top());
        tokens.pop();
        auto assigner = std::move(tokens.top());
        tokens.pop();
        auto propName = std::move(tokens.top());
        tokens.pop();

        if (propName->GetTokenType() == T_IDENTIFIER &&
            (
                    val->GetTokenType() == T_IDENTIFIER ||
                    val->GetTokenType() == T_LBOOL ||
                    val->GetTokenType() == T_LNUMBER ||
                    val->GetTokenType() == T_LFNUMBER ||
                    val->GetTokenType() == T_LSTRING
            ) &&
            (
                    assigner->GetTokenType() == T_VARASSIGN ||
                    assigner->GetTokenType() == T_PROPASSIGN)
                )
        {
            if (val->GetTokenType() == T_LBOOL)
                currentSt->SetVariable((char *) propName->GetValue(),
                                       (bool *) val->GetValue());
            else if (val->GetTokenType() == T_LFNUMBER)
                currentSt->SetVariable<double>((char *) propName->GetValue(),
                                               (double *) val->GetValue());
            else if (val->GetTokenType() == T_LNUMBER)
                currentSt->SetVariable<int64_t>((char *) propName->GetValue(),
                                               (int64_t *) val->GetValue());
            else if (val->GetTokenType() == T_LSTRING)
                currentSt->SetVariable<char>((char *) propName->GetValue(),
                                             (char*) val->GetValue());
            else if(val->GetTokenType() == T_IDENTIFIER)
                SetFromSymbolTables(currentSt, CopyStr((char *) propName->GetValue()), (char *) val->GetValue(), mistakes);

            return true;
        }
        else
        {
            return false;
        }
    }

    void StackedStyleParser::AssignProps(std::stack<std::unique_ptr<Token>> &tokens,
                                         std::shared_ptr<SymbolTable> &currentSt,
                                         std::vector<CompilationMistake>& mistakes)
    {
        if(tokens.size() < 2)
            throw ParsingException(R"(Unexpected symbol "}")");

        tokens.pop(); // remove '{'

        auto objName = std::move(tokens.top());
        tokens.pop();

        std::stringstream ss;
        if(!tokens.empty() && tokens.top()->GetTokenType() == T_IDENTITY)
        {
            ss << "#";
            tokens.pop();
        }

        ss << (char*) objName->GetValue();

        SaveTopSymbolTable(ss.str());

        currentSt = m_symbolTables.back();
    }

    void StackedStyleParser::SaveTopSymbolTable(std::string name)
    {
        auto topSymbolTable = m_symbolTables.back();
        if(m_variables.find(name) != m_variables.end())
        {
            m_variables[std::move(name)]->Append(*topSymbolTable);
        }
        else
        {
            m_variables[std::move(name)] = topSymbolTable;
        }
        m_symbolTables.pop_back();
    }

    char *StackedStyleParser::CopyStr(const char* str)
    {
        if(!str)
            return nullptr;

        auto copied = new char[strlen(str)];
        strcpy(copied, str);

        return copied;
    }
}