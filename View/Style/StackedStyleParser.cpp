//
// Created by JajaFil on 3/7/2022.
//

#include <fstream>
#include <sstream>
#include <stack>
#include <iostream>
#include "StackedStyleParser.h"
#include "Tokenizer.h"
#include "../Exceptions/FileNotFoundException.h"
#include "../Exceptions/ParsingException.h"

namespace Trema::View
{
    StackedStyleParser::StackedStyleParser()
    {

    }

    void StackedStyleParser::Apply(std::shared_ptr<IWindow> window)
    {

    }

    void StackedStyleParser::ParseFromCode(const std::string &code)
    {
        Tokenizer tokenizer(code);

        if(tokenizer.Empty())
            return;

        std::stack<std::unique_ptr<Token>> tokens;

        auto currentToken = tokenizer.GetNextToken();
        unsigned int scope = 0;

        auto currentSt = std::make_shared<SymbolTable>();
        m_symbolTables.push_back(currentSt);

        while(currentToken->GetTokenType() != T_STOP)
        {
            switch(currentToken->GetTokenType())
            {
                case T_IDENTITY:
                case T_IDENTIFIER:
                case T_LBOOL:
                case T_LNUMBER:
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

                    m_variables[ss.str()] = m_symbolTables.back();
                    m_symbolTables.pop_back();

                    currentSt = m_symbolTables.back();

                    break;
                }
                case T_ENDINS:
                {
                    if (tokens.size() < 3)
                        throw ParsingException(R"(Unexpected symbol ";")");

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
                            else if (val->GetTokenType() == T_LNUMBER)
                                currentSt->SetVariable<double>((char *) propName->GetValue(),
                                                                  (double *) val->GetValue());
                            else if (val->GetTokenType() == T_LSTRING)
                                currentSt->SetVariable<char>((char *) propName->GetValue(),
                                                                (char *) val->GetValue());
                            else if(val->GetTokenType() == T_IDENTIFIER)
                                SetFromSymbolTables(currentSt, (char *) propName->GetValue(), (char *) val->GetValue());
                    }
                    else
                    {
                        throw ParsingException(R"(Unexpected symbol ";")");
                    }
                    break;
                }
                case T_LPAR:
                case T_RPAR:
                case T_STOP:
                    break;
                    /*case T_IDENTIFIER:
                        if (nextToken->GetTokenType() == T_VARASSIGN ||
                            nextToken->GetTokenType() == T_PROPASSIGN) // Value assignment
                        {
                            tokens.push(std::move(currentToken));
                        }
                        else
                        {
                            auto varName = std::string((char*)currentToken->GetValue());
                            if(!m_symbolTable.HasVariable(varName))
                            {
                                std::stringstream ss;
                                ss << "Undeclared identifier \"" << varName << "\"";
                                throw ParsingException(ss.str().c_str());
                            }

                            auto var = m_symbolTable.GetVariable(varName);
                            if(var->GetType() == TYPE_BOOL)
                                tokens.push(std::move(std::make_unique<Token>(T_LBOOL, currentToken->GetPosition(), var->GetValue())));
                            else if(var->GetType() == TYPE_STR)
                                tokens.push(std::move(std::make_unique<Token>(T_LSTRING, currentToken->GetPosition(), var->GetValue())));
                            else if(var->GetType() == TYPE_NUM)
                                tokens.push(std::move(std::make_unique<Token>(T_LNUMBER, currentToken->GetPosition(), var->GetValue())));
                        }
                        break;
                    case T_VARASSIGN:
                        break;*/
            }

            currentToken = tokenizer.GetNextToken();
        }

        m_variables["*"] = std::move(m_symbolTables.front());
        m_symbolTables.pop_front();
        // auto t = tokenizer.GetNextToken();
        //std::cout << t->GetIdentity();
        //std::cout << m_symbolTable;

        for(const auto& [name, st] : m_variables)
        {
            std::cout << name << ":\n" << *st;
        }

        std::cout << std::flush;
    }

    void StackedStyleParser::ParseFromFile(const std::string &path)
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

        ParseFromCode(code.str());
    }

    void StackedStyleParser::SetFromSymbolTables(const std::shared_ptr<SymbolTable>& symbolTable, const char *propName, char *varName)
    {
        for(const auto& st : m_symbolTables)
        {
            if(st->HasVariable(varName))
            {
                auto v = st->GetVariable(varName);
                switch(v->GetType())
                {
                    case TYPE_NUM:
                        symbolTable->SetVariable<double>(propName, (double*)v->GetValue());
                        return;
                    case TYPE_STR:
                        symbolTable->SetVariable<char>(propName, (char*)v->GetValue());
                        return;
                    case TYPE_BOOL:
                        symbolTable->SetVariable<bool>(propName, (bool*)v->GetValue());
                        return;
                }
            }
        }

        std::stringstream ss;
        ss << "Undefined symbol \"" << varName << "\"";
        throw ParsingException(ss.str().c_str());
    }
}