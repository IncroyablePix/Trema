//
// Created by JajaFil on 3/7/2022.
//

#include <fstream>
#include <sstream>
#include "StackedStyleParser.h"
#include "Tokenizer.h"
#include "../Exceptions/FileNotFoundException.h"

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