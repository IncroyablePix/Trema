#include <catch2/catch_test_macros.hpp>
#include <Observable/Collections/ObservableCollection.h>

using namespace Trema::Observable;

namespace Trema::Test::Observable
{
    TEST_CASE("Test subscribe and notify")
    {
        // Given
        ObservableCollection<std::vector<int>> collection;
        int value = 0;

        // When
        collection.GetContainer().emplace_back(1);
        collection.Subscribe("TestObserver", [&value](ObservableCollection<std::vector<int>>& v) { value = v.GetContainer().size(); });
        collection.Notify();

        // Then
        REQUIRE(value == 1);
    }

    TEST_CASE("Test unsubscribe")
    {
        // Given
        std::string observerName = "TestObserver";
        ObservableCollection<std::vector<int>> collection;
        int value = 0;

        // When
        collection.GetContainer().emplace_back(1);
        collection.Subscribe(observerName, [&value](ObservableCollection<std::vector<int>>& v) { value = v.GetContainer().size(); });
        collection.Unsubscribe(observerName);
        collection.Notify();

        // Then
        REQUIRE(value == 0);
    }
}