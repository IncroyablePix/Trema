//
// Created by JajaFil on 3/7/2022.
//

#include <iostream>
#include <fstream>
#include <stack>
#include "StackedStyleParser.h"
#include "../../Exceptions/FileNotFoundException.h"
#include "../../Exceptions/ParsingException.h"

namespace Trema::View
{
    StackedStyleParser::StackedStyleParser()
    {

    }

    void StackedStyleParser::ParseFromCode(const std::string &code, std::vector<CompilationMistake>& mistakes)
    {
        Tokenizer tokenizer(code, mistakes);

        if(tokenizer.Empty())
            return;

        std::stack<std::unique_ptr<Token>> tokens;
        std::stack<std::unique_ptr<Token>> operators;

        auto currentSt = std::make_shared<SymbolTable>();
        m_symbolTables.push_back(currentSt);

        auto currentToken = tokenizer.GetNextToken();
        while(!tokenizer.Empty() && currentToken->GetTokenType() != T_STOP)
        {
            switch(currentToken->GetTokenType())
            {
                case T_IDENTITY:
                case T_IDENTIFIER:
                case T_LBOOL:
                case T_LSTRING:
                case T_PROPASSIGN:
                case T_VARASSIGN:
                case T_LNUMBER:
                case T_LFNUMBER:
                    tokens.push(std::move(currentToken));
                    break;
                case T_OPERATOR:
                    ProcessOperators(operators, currentToken, tokens, mistakes);
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
                    if(!AssignVar(tokens, operators, currentSt, mistakes))
                    {
                        mistakes.emplace_back(
                                CompilationMistake
                                {
                                    .Line = currentToken->GetLine(),
                                    .Position = currentToken->GetPosition(),
                                    .Code = ErrorCode::UnexpectedToken,
                                    .Extra = ";"
                                });
                    }
                    break;

                case T_LPAR:
                case T_RPAR:
                case T_STOP:
                case T_COMMENT:
                    break;
            }

            currentToken = tokenizer.GetNextToken();
        }

        SaveTopSymbolTable("#");
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
                        symbolTable->SetVariable<int64_t>(propName, v->CopyValue());
                        return;
                    case TYPE_FLOAT:
                        symbolTable->SetVariable<double>(propName, v->CopyValue());
                        return;
                    case TYPE_STR:
                        symbolTable->SetVariable<char>(propName, v->CopyValue());
                        return;
                    case TYPE_BOOL:
                        symbolTable->SetVariable<bool>(propName, v->CopyValue());
                        return;
                }
            }
        }

        if(propName != nullptr)
            delete[] propName;

        mistakes.emplace_back(CompilationMistake { .Line = 1, .Position = 0, .Code = ErrorCode::UndefinedSymbol, .Extra = std::string(varName) });
    }

    std::any StackedStyleParser::GetNextTokenValue(std::stack<std::unique_ptr<Token>>& tokens, std::vector<CompilationMistake> &mistakes) const
    {
        auto token = std::move(tokens.top());
        tokens.pop();

        if(token->GetTokenType() == T_IDENTIFIER)
        {
            for(const auto& st : m_symbolTables)
            {
                if(st->HasVariable(token->GetValue().String))
                {
                    auto v = st->GetVariable(token->GetValue().String);
                    if(v->GetType() == TYPE_NUM)
                    {
                        return *v->GetValue().Integer;
                    }
                    else if(v->GetType() == TYPE_FLOAT)
                    {
                        return *v->GetValue().Float;
                    }
                    else
                    {
                        mistakes.emplace_back(CompilationMistake { .Line = token->GetLine(), .Position = token->GetPosition(), .Code = ErrorCode::TypeMismatch, .Extra = std::string(token->GetValue().String) });
                        return {};
                    }
                }
            }
        }
        else if(token->GetTokenType() == T_LNUMBER)
        {
            return *token->GetValue().Integer;
        }
        else if(token->GetTokenType() == T_LFNUMBER)
        {
            return *token->GetValue().Float;
        }
        else
        {
            // TODO: process error
            mistakes.emplace_back(CompilationMistake { .Line = token->GetLine(), .Position = token->GetPosition(), .Code = ErrorCode::UnexpectedToken, .Extra = token->GetIdentity() });
        }

        return {};
    }

    bool StackedStyleParser::ProcessOperators(std::stack<std::unique_ptr<Token>> &operators,
                                              std::unique_ptr<Token> &currentOperator,
                                              std::stack<std::unique_ptr<Token>> &tokens,
                                              std::vector<CompilationMistake> &mistakes)
    {
        while(!operators.empty())
        {
            const auto& operator2Token = operators.top();
            const auto& op1 = m_operationsTable.GetOperator(currentOperator->GetValue().String);
            const auto& op2 = m_operationsTable.GetOperator(operator2Token->GetValue().String);

            if(op2.Priority > op1.Priority || (op2.Priority == op1.Priority && op2.IsLeftAssociative))
            {
                operators.pop();

                const auto value1 = GetNextTokenValue(tokens, mistakes);
                const auto value2 = GetNextTokenValue(tokens, mistakes);

                const auto result = op2.Operation(value2, value1);

                if(result.type() == typeid(double))
                {
                    const auto doublePtr = new double(std::any_cast<double>(result));
                    auto t = std::make_unique<Token>(T_LFNUMBER, currentOperator->GetPosition(),
                                                     currentOperator->GetLine(), TokenValue{ .Float = doublePtr });
                    tokens.push(std::move(t));
                }
                else if(result.type() == typeid(int64_t))
                {
                    const auto intPtr = new int64_t(std::any_cast<int64_t>(result));
                    auto t = std::make_unique<Token>(T_LNUMBER, currentOperator->GetPosition(),
                                                     currentOperator->GetLine(), TokenValue{ .Integer = intPtr});
                    tokens.push(std::move(t));
                }
            }
            else
            {
                break;
            }
        }

        operators.push(std::move(currentOperator));
        return true;
    }

    bool StackedStyleParser::AssignVar(std::stack<std::unique_ptr<Token>>& tokens,
                                       std::stack<std::unique_ptr<Token>>& operators,
                                       const std::shared_ptr<SymbolTable>& currentSt,
                                       std::vector<CompilationMistake>& mistakes)
    {
        // Shunting Yard
        while(!operators.empty())
        {
            const auto operatorToken = std::move(operators.top());
            operators.pop();

            const auto value1 = GetNextTokenValue(tokens, mistakes);
            const auto value2 = GetNextTokenValue(tokens, mistakes);

            const auto& op2 = m_operationsTable.GetOperator(operatorToken->GetValue().String);
            const auto result = op2.Operation(value2, value1);

            if(result.type() == typeid(double))
            {
                const auto doublePtr = new double(std::any_cast<double>(result));
                auto t = std::make_unique<Token>(T_LFNUMBER, operatorToken->GetPosition(),
                                                 operatorToken->GetLine(), TokenValue{ .Float = doublePtr });
                tokens.push(std::move(t));
            }
            else if(result.type() == typeid(int64_t))
            {
                const auto intPtr = new int64_t(std::any_cast<int64_t>(result));
                auto t = std::make_unique<Token>(T_LNUMBER, operatorToken->GetPosition(),
                                                 operatorToken->GetLine(), TokenValue{ .Integer = intPtr});
                tokens.push(std::move(t));
            }
        }

        //
        if (tokens.size() < 3)
            return false;

        // Assign to variable
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
                currentSt->SetVariable<bool>(propName->GetValue().String, val->GetValue().Clone<bool>());
            else if (val->GetTokenType() == T_LFNUMBER)
                currentSt->SetVariable<double>(propName->GetValue().String, val->GetValue().Clone<double>());
            else if (val->GetTokenType() == T_LNUMBER)
                currentSt->SetVariable<int64_t>(propName->GetValue().String, val->GetValue().Clone<int64_t>());
            else if (val->GetTokenType() == T_LSTRING)
                currentSt->SetVariable<char>(propName->GetValue().String, val->GetValue().Clone<char*>());
            else if(val->GetTokenType() == T_IDENTIFIER)
                SetFromSymbolTables(currentSt, CopyStr(propName->GetValue().String), val->GetValue().String, mistakes);

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

        // Getting identifier
        auto topToken = std::move(tokens.top());
        tokens.pop();

        std::stringstream ss;
        if(topToken->GetTokenType() == T_IDENTITY)
        {
            ss << "#";
        }
        else if(topToken->GetTokenType() == T_IDENTIFIER)
        {
            if(!tokens.empty() && tokens.top()->GetTokenType() == T_IDENTITY)
            {
                ss << "#";
                tokens.pop();
            }
            ss << topToken->GetValue().String;
        }

        SaveTopSymbolTable(ss.str());

        currentSt = m_symbolTables.back();
    }

    void StackedStyleParser::SaveTopSymbolTable(std::string name)
    {
        auto topSymbolTable = m_symbolTables.back();
        if(m_variables.contains(name))
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