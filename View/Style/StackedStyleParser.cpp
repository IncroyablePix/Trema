//
// Created by JajaFil on 3/7/2022.
//

#include <fstream>
#include <sstream>
#include <stack>
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

        std::stack<std::unique_ptr<Token>> ops;
        std::stack<std::unique_ptr<Token>> vals;

        auto currentToken = tokenizer.GetNextToken();
        auto nextToken = tokenizer.GetNextToken();

        while(currentToken->GetTokenType() != T_STOP)
        {
            switch(currentToken->GetTokenType())
            {
                case T_ENDINS:

                    break;
                case T_LBOOL:
                case T_LNUMBER:
                case T_LSTRING:
                    vals.push(std::move(currentToken));
                case T_IDENTIFIER:
                    if (nextToken->GetTokenType() == T_VARASSIGN ||
                        nextToken->GetTokenType() == T_PROPASSIGN) // Value assignment
                    {
                        ops.push(std::move(currentToken));
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
                            vals.push(std::move(std::make_unique<Token>(T_LBOOL, currentToken->GetPosition(), var->GetValue())));
                        else if(var->GetType() == TYPE_STR)
                            vals.push(std::move(std::make_unique<Token>(T_LSTRING, currentToken->GetPosition(), var->GetValue())));
                        else if(var->GetType() == TYPE_NUM)
                            vals.push(std::move(std::make_unique<Token>(T_LNUMBER, currentToken->GetPosition(), var->GetValue())));
                    }
                    break;
                case T_VARASSIGN:
                    break;
            }
        }
        // auto t = tokenizer.GetNextToken();
        //std::cout << t->GetIdentity();
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
}