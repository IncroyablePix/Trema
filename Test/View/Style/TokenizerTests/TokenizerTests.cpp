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
        while(t.GetNextToken())
        {
            count ++;
        }

        // Then
        REQUIRE(count == 9);
    }
}