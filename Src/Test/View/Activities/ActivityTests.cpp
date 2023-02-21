#include <catch2/catch_test_macros.hpp>
#include <View/Activities/Activity.h>
#include "View/Components/Widgets/Button.h"
#include "TestActivity.h"

using namespace Trema::View;

namespace Trema::Test::View
{
    class MockElement : public Trema::View::GuiElement
    {
    public:
        explicit MockElement(std::shared_ptr<GuiElement> parent, std::string name) :
            Trema::View::GuiElement(std::move(parent), std::move(name))
        {

        }

        void Show() override {}
    };

    TEST_CASE("Get by ID in activity")
    {
        // Given
        std::string elementId = "myElement";
        std::string elementName("My test element");
        Intent intent;
        TestActivity activity(intent);
        auto guiElement = std::make_shared<MockElement>(nullptr, elementName);
        activity.AddElementId(elementId, guiElement);

        // When
        auto result = activity.GetElementById<MockElement>(elementId);

        // Then
        REQUIRE(result != nullptr);
        REQUIRE(elementName == result->NameId());
    }

    TEST_CASE("Get by ID in activity with wrong type")
    {
        // Given
        std::string elementId = "myElement";
        std::string elementName("My test element");
        Intent intent;
        TestActivity activity(intent);
        auto guiElement = std::make_shared<MockElement>(nullptr, elementName);
        activity.AddElementId(elementId, guiElement);

        // When
        auto result = activity.GetElementById<Button>(elementId);

        // Then
        REQUIRE(result == nullptr);
    }

    TEST_CASE("Get element with non-existant ID")
    {
        // Given
        std::string elementId = "myElement";
        std::string elementName("My test element");
        Intent intent;
        TestActivity activity(intent);
        auto guiElement = std::make_shared<MockElement>(nullptr, elementName);
        activity.AddElementId(elementId, guiElement);

        // When
        auto result = activity.GetElementById<MockElement>("nonExistantId");

        // Then
        REQUIRE(result == nullptr);
    }

    TEST_CASE("Get value from intent")
    {
        // Given
        std::string intentReferenceId = "myIntentValue";
        std::string intentValue("Test intent value");
        Intent intent;
        intent.SetStringExtra(intentReferenceId, intentValue);
        TestActivity activity(intent);

        // When
        auto result = activity.GetStringFromIntent(intentReferenceId);

        // Then
        REQUIRE(result == intentValue);
    }
}