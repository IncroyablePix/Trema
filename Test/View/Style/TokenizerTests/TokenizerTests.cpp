//
// Created by JajaFil on 4/9/2022.
//

#include "../../../../Src/View/Style/Tokenizer/Tokenizer.h"
#include <catch2/catch_test_macros.hpp>

using namespace Trema::View;

namespace Trema::Test::View
{
    TEST_CASE("Getting the good amount of tokens")
    {
        // Given
        std::string code = "#element { prop: variable; }";
        std::vector<CompilationMistake> mistakes;
        int count = 0;

        // When
        Tokenizer t(code, mistakes);
        while(!t.Empty())
        {
            auto token = t.GetNextToken();
            count ++;
        }

        // Then
        REQUIRE(count == 9);
    }

    TEST_CASE("Last token is T_STOP")
    {
        // Given
        std::string code = "#element { prop: variable; }";
        std::vector<CompilationMistake> mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        while(!t.Empty())
        {
            token = t.GetNextToken();
        }

        // Then
        REQUIRE(token->GetTokenType() == T_STOP);
    }

    TEST_CASE("Identifies litteral string")
    {
        // Given
        std::string code = R"("Hello, I'm testing out my code")";
        std::vector<CompilationMistake> mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LSTRING);
        REQUIRE(std::string((char*)token->GetValue()) == "Hello, I'm testing out my code");
    }

    TEST_CASE("Identifies boolean value")
    {
        // Given
        std::string code = "false";
        std::vector<CompilationMistake> mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LBOOL);
        REQUIRE(*((bool*) token->GetValue()) == false);
    }

    TEST_CASE("Identifies number as float")
    {
        // Given
        std::string code = "1.5";
        std::vector<CompilationMistake> mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LFNUMBER);
        REQUIRE(*((double*) token->GetValue()) == 1.5);
    }

    TEST_CASE("Identifies number as integer")
    {
        // Given
        std::string code = "34";
        std::vector<CompilationMistake> mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LNUMBER);
        REQUIRE(*((int64_t *) token->GetValue()) == 34);
    }

    TEST_CASE("Has error for unfinished string")
    {
        // Given
        std::string code = R"("Hello, I'm testing out my code\n)";
        std::vector<CompilationMistake> mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);

        // Then
        REQUIRE(mistakes.size() == 1);
        REQUIRE(mistakes[0].Code == UnfinishedString);
    }
}