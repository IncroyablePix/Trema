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
        Tokenizer t(code, mistakes);
        int count = 0;

        // When
        while(!t.Empty())
        {
            auto token = t.GetNextToken();
            token->DeleteValue();
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
        Tokenizer t(code, mistakes);
        std::unique_ptr<Token> token;

        // When
        while(!t.Empty())
        {
            token = t.GetNextToken();
            token->DeleteValue();
        }

        // Then
        REQUIRE(token->GetTokenType() == T_STOP);
    }
}