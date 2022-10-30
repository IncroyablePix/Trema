//
// Created by JajaFil on 4/30/2022.
//

#include <catch2/catch_test_macros.hpp>
#include "Utils/StringConversion.h"

using namespace Trema::Utils;

namespace Trema::Test::Utils
{
    TEST_CASE("Boolean extraction")
    {
        // Given
        std::string strTrue("true");
        std::string strFalse("false");

        // When
        bool bTrue = StrToBool(strTrue);
        bool bFalse = StrToBool(strFalse);

        // Then
        REQUIRE(bTrue);
        REQUIRE(!bFalse);
    }

    TEST_CASE("Invalid boolean extraction")
    {
        // Given
        std::string strInvalid("invalid");

        // When
        bool bInvalid = StrToBool(strInvalid);

        // Then
        REQUIRE(!bInvalid);
    }

    TEST_CASE("Float extraction")
    {
        // Given
        std::string strFloat("3.14");

        // When
        float f = StrToFloat(strFloat);

        // Then
        REQUIRE(f == 3.14f);
    }

    TEST_CASE("Invalid float extraction")
    {
        // Given
        std::string strInvalid("invalid");

        // When
        float f = StrToFloat(strInvalid);

        // Then
        REQUIRE(f == 0.0f);
    }

    TEST_CASE("Integer extraction")
    {
        // Given
        std::string strInt("42");

        // When
        int i = StrToInt(strInt);

        // Then
        REQUIRE(i == 42);
    }

    TEST_CASE("Invalid integer extraction")
    {
        // Given
        std::string strInvalid("invalid");

        // When
        int i = StrToInt(strInvalid);

        // Then
        REQUIRE(i == 0);
    }

    TEST_CASE("Is float")
    {
        // Given
        std::string strFloat("3.14");

        // When
        bool isFloat = IsFloat(strFloat);

        // Then
        REQUIRE(isFloat);
    }

    TEST_CASE("Is not float")
    {
        // Given
        std::string strInt("f42gfd");

        // When
        bool isFloat = IsFloat(strInt);

        // Then
        REQUIRE(!isFloat);
    }

    TEST_CASE("Is int float")
    {
        // Given
        std::string strInt("42");

        // When
        bool isFloat = IsFloat(strInt);

        // Then
        REQUIRE(isFloat);
    }
}