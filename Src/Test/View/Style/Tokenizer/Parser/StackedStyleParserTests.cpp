//
// Created by JajaFil on 4/9/2022.
//

#include "../../../../../Trema/View/Style/Tokenizer/Tokenizer.h"
#include "../../../../../Trema/View/Style/Parser/StackedStyleParser.h"
#include <catch2/catch_test_macros.hpp>
#include <sstream>

using namespace Trema::View;

namespace Trema::Test::View
{
    TEST_CASE("Simple addition")
    {
        // Given
        std::string code = "three: 2 + 1;";
        MistakesContainer mistakes;

        // When
        StackedStyleParser parser(mistakes);
        parser.ParseFromCode(code);

        // Then
        auto variables = parser.GetVariables();
        auto three = *variables["#"]->GetVariable("three")->GetValue().Integer;
        REQUIRE(three == 3);
    }

    TEST_CASE("Multiplication has precedence over addition")
    {
        // Given
        std::string code = "five: 2 + 1 * 3;";
        MistakesContainer mistakes;

        // When
        StackedStyleParser parser(mistakes);
        parser.ParseFromCode(code);

        // Then
        auto variables = parser.GetVariables();
        auto five = *variables["#"]->GetVariable("five")->GetValue().Integer;
        REQUIRE(five == 5);
    }

    TEST_CASE("Multiplication has precedence over addition but it's before the addition")
    {
        // Given
        std::string code = "five: 3 * 1 + 2;";
        MistakesContainer mistakes;

        // When
        StackedStyleParser parser(mistakes);
        parser.ParseFromCode(code);

        // Then
        auto variables = parser.GetVariables();
        auto five = *variables["#"]->GetVariable("five")->GetValue().Integer;
        REQUIRE(five == 5);
    }

    TEST_CASE("Using variables")
    {
        // Given
        std::string code = "two: 2; five: 3 + two;";
        MistakesContainer mistakes;

        // When
        StackedStyleParser parser(mistakes);
        parser.ParseFromCode(code);

        // Then
        auto variables = parser.GetVariables();
        auto five = *variables["#"]->GetVariable("five")->GetValue().Integer;
        auto two = *variables["#"]->GetVariable("two")->GetValue().Integer;

        REQUIRE(two == 2);
        REQUIRE(five == 5);
    }

    TEST_CASE("Using variable in sub-scope")
    {
        // Given
        std::string code = "two: 2; #scope { five: 3 + two; }";
        MistakesContainer mistakes;

        // When
        StackedStyleParser parser(mistakes);
        parser.ParseFromCode(code);

        // Then
        auto variables = parser.GetVariables();
        auto five = *variables["#scope"]->GetVariable("five")->GetValue().Integer;
        auto two = *variables["#"]->GetVariable("two")->GetValue().Integer;

        REQUIRE(two == 2);
        REQUIRE(five == 5);
    }
}
