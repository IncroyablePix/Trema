#include "../../../../../Trema/View/Style/Tokenizer/Tokenizer.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Trema::View;

namespace Trema::Test::View
{
    TEST_CASE("Getting the good amount of tokens")
    {
        // Given
        std::string code = "#element { prop: variable; }";
        MistakesContainer mistakes;
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
        MistakesContainer mistakes;
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
        MistakesContainer mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LSTRING);
        REQUIRE(std::string(token->GetValue().String) == "Hello, I'm testing out my code");
    }

    TEST_CASE("Identifies boolean value")
    {
        // Given
        std::string code = "false";
        MistakesContainer mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LBOOL);
        REQUIRE(*(token->GetValue().Boolean) == false);
    }

    TEST_CASE("Identifies number as float")
    {
        // Given
        std::string code = "1.5";
        MistakesContainer mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LFNUMBER);
        REQUIRE(*(token->GetValue().Float) == 1.5);
    }

    TEST_CASE("Identifies number as integer")
    {
        // Given
        std::string code = "34";
        MistakesContainer mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_LNUMBER);
        REQUIRE(*(token->GetValue().Integer) == 34);
    }

    TEST_CASE("Has error for unfinished string")
    {
        // Given
        std::string code = R"("Hello, I'm testing out my code\n)";
        MistakesContainer mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);

        // Then
        REQUIRE(mistakes.Size() == 1);
        REQUIRE(mistakes[0].Code == UnfinishedString);
    }

    TEST_CASE("Ignores comments")
    {
        // Given
        std::string code = R"(#test { property: /* This is a comment */ "value"; /* This is also a comment */ })";
        MistakesContainer mistakes;
        std::unique_ptr<Token> token;

        // When
        Tokenizer t(code, mistakes);

        // Then
        REQUIRE(mistakes.Empty());
        REQUIRE(t.Size() == 11);
    }

    TEST_CASE("Catches comment")
    {
        // Given
        std::string comment = "Testing out my stuff";
        MistakesContainer mistakes;
        std::stringstream ss;
        ss << "/*" << comment << "*/";
        std::unique_ptr<Token> token;
        std::string code { ss.str() };

        // When
        Tokenizer t(code, mistakes);
        token = t.GetNextToken();

        // Then
        REQUIRE(token->GetTokenType() == T_COMMENT);
        REQUIRE(std::string(token->GetValue().String) == comment);
    }
}