#include <catch2/catch_test_macros.hpp>
#include <View/Components/Style/ElementStyle.h>

using namespace Trema::View;

namespace Trema::Test::View
{
    TEST_CASE("Set alignment from string")
    {
        // Given
        ElementStyle elementStyle;
        std::string alignment = "center";

        // When
        elementStyle.SetHorizontalAlignment(alignment);

        // Then
        REQUIRE(elementStyle.GetHorizontalAlignment() == Alignment::Center);
    }

    TEST_CASE("Set alignment from string with invalid value")
    {
        // Given
        ElementStyle elementStyle;
        std::string alignment = "invalid";

        // When
        elementStyle.SetHorizontalAlignment(alignment);

        // Then
        REQUIRE(elementStyle.GetHorizontalAlignment() == Alignment::Start);
    }

    TEST_CASE("Set orientation from string")
    {
        // Given
        ElementStyle elementStyle;
        std::string orientation = "column";

        // When
        elementStyle.SetOrientation(orientation);

        // Then
        REQUIRE(elementStyle.GetOrientation() == Orientation::Column);
    }

    TEST_CASE("Set orientation from string with invalid value")
    {
        // Given
        ElementStyle elementStyle;
        std::string orientation = "invalid";

        // When
        elementStyle.SetOrientation(orientation);

        // Then
        REQUIRE(elementStyle.GetOrientation() == Orientation::Row);
    }
}
