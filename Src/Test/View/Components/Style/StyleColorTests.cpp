#include <catch2/catch_test_macros.hpp>
#include <View/Components/Style/StyleColor.h>

using namespace Trema::View;

namespace Trema::Test::View
{
    TEST_CASE("Empty color should not have color")
    {
        // Given
        StyleColor styleColor;

        // When
        bool hasColor = styleColor.HasColor();

        // Then
        REQUIRE(hasColor == false);
    }

    TEST_CASE("Create StyleColor from ImVec4")
    {
        // Given
        ImVec4 color = { 0.1f, 0.2f, 0.3f, 0.4f };

        // When
        StyleColor styleColor(color);

        // Then
        REQUIRE(styleColor.HasColor());
        REQUIRE(styleColor.GetColor().x == color.x);
        REQUIRE(styleColor.GetColor().y == color.y);
        REQUIRE(styleColor.GetColor().z == color.z);
        REQUIRE(styleColor.GetColor().w == color.w);
    }

    TEST_CASE("Set color from unsigned int")
    {
        // Given
        unsigned int color = 0xCC0000FF;
        StyleColor styleColor;

        // When
        styleColor.SetColor(color);

        // Then
        REQUIRE(styleColor.HasColor());
        REQUIRE(styleColor.GetColor().x == 0.8f);
        REQUIRE(styleColor.GetColor().y == 0.0f);
        REQUIRE(styleColor.GetColor().z == 0.0f);
        REQUIRE(styleColor.GetColor().w == 1.0f);
    }

    TEST_CASE("Set color from ImVec4")
    {
        // Given
        ImVec4 color = { 0.1f, 0.2f, 0.3f, 0.4f };
        StyleColor styleColor;

        // When
        styleColor.SetColor(color);

        // Then
        REQUIRE(styleColor.HasColor());
        REQUIRE(styleColor.GetColor().x == color.x);
        REQUIRE(styleColor.GetColor().y == color.y);
        REQUIRE(styleColor.GetColor().z == color.z);
        REQUIRE(styleColor.GetColor().w == color.w);
    }

    TEST_CASE("Set color from int")
    {
        // Given
        int color = 0xCC0000FF;
        StyleColor styleColor;

        // When
        styleColor.SetColor(color);

        // Then
        REQUIRE(styleColor.HasColor());
        REQUIRE(styleColor.GetColor().x == 0.8f);
        REQUIRE(styleColor.GetColor().y == 0.0f);
        REQUIRE(styleColor.GetColor().z == 0.0f);
        REQUIRE(styleColor.GetColor().w == 1.0f);
    }
}