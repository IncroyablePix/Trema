//
// Created by Benjam on 10/31/2022.
//

#include <catch2/catch_test_macros.hpp>
#include <View/Activities/Activity.h>
#include <View/Activities/ThreadSafeStateManager.h>
#include "TestActivity.h"
#include <iostream>

using namespace Trema::View;

namespace Trema::Test::View
{
    TEST_CASE("Only last pushed is considered")
    {
        // Given
        Intent intent;
        auto testActivity1 = std::make_unique<TestActivity>(intent, nullptr);
        auto testActivity2 = std::make_unique<TestActivity>(intent, nullptr);
        ThreadSafeStateManager threadSafeStateManager;
        threadSafeStateManager.PushPending(std::move(testActivity1));
        threadSafeStateManager.PushPending(std::move(testActivity2));

        // When
        threadSafeStateManager.UpdateState();

        // Then
        REQUIRE(threadSafeStateManager.Count() == 1);
    }

    TEST_CASE("Only last pushed is considered with multiple updates")
    {
        // Given
        Intent intent1, intent2;
        auto testActivity1 = std::make_unique<TestActivity>(std::move(intent1), nullptr);
        auto testActivity2 = std::make_unique<TestActivity>(std::move(intent2), nullptr);
        ThreadSafeStateManager threadSafeStateManager;
        threadSafeStateManager.PushPending(std::move(testActivity1));
        threadSafeStateManager.PushPending(std::move(testActivity2));

        // When
        threadSafeStateManager.UpdateState();
        threadSafeStateManager.UpdateState();
        threadSafeStateManager.UpdateState();

        // Then
        REQUIRE(threadSafeStateManager.Count() == 1);
    }

    TEST_CASE("Two activities can be pushed within multiple updates")
    {
        // Given
        auto testActivity1 = std::make_unique<TestActivity>(Intent(), nullptr);
        auto testActivity2 = std::make_unique<TestActivity>(Intent(), nullptr);
        ThreadSafeStateManager threadSafeStateManager;

        // When
        threadSafeStateManager.PushPending(std::move(testActivity1));
        threadSafeStateManager.UpdateState();
        threadSafeStateManager.PushPending(std::move(testActivity2));
        threadSafeStateManager.UpdateState();

        // Then
        REQUIRE(threadSafeStateManager.Count() == 2);
    }

    TEST_CASE("Resume activity")
    {
        // Given
        bool resumed = false;
        Intent intent1;
        auto testActivity1 = std::make_unique<TestActivity>(std::move(intent1), nullptr);
        testActivity1->OnResultCallback = [&resumed](uint16_t requestCode, uint16_t resultCode, Intent intent)
        {
            resumed = true;
        };

        Intent intent2;
        auto testActivity2 = std::make_unique<TestActivity>(std::move(intent2), nullptr);

        ThreadSafeStateManager threadSafeStateManager;
        threadSafeStateManager.PushPending(std::move(testActivity1));
        threadSafeStateManager.UpdateState();
        threadSafeStateManager.PushPending(std::move(testActivity2));
        threadSafeStateManager.UpdateState();

        // When
        threadSafeStateManager.QuitPending(0, 0, Intent());
        threadSafeStateManager.UpdateState();

        // Then
        REQUIRE(resumed);
    }

    TEST_CASE("Updates with good deltaTime")
    {
        // Given
        auto givenDeltaTime = 1.0;
        auto receivingDeltaTime = (double)NAN;
        auto testActivity1 = std::make_unique<TestActivity>(Intent(), nullptr);
        testActivity1->OnUpdateCallback = [&receivingDeltaTime](double deltaTime)
        {
            receivingDeltaTime = deltaTime;
        };

        ThreadSafeStateManager threadSafeStateManager;
        threadSafeStateManager.PushPending(std::move(testActivity1));
        threadSafeStateManager.UpdateState();

        // When
        threadSafeStateManager.UpdateCurrentActivity(givenDeltaTime);

        // Then
        REQUIRE(receivingDeltaTime == givenDeltaTime);
    }

    TEST_CASE("Clear state manager")
    {
        // Given
        auto testActivity1 = std::make_unique<TestActivity>(Intent(), nullptr);
        auto testActivity2 = std::make_unique<TestActivity>(Intent(), nullptr);
        ThreadSafeStateManager threadSafeStateManager;
        threadSafeStateManager.PushPending(std::move(testActivity1));
        threadSafeStateManager.UpdateState();
        threadSafeStateManager.PushPending(std::move(testActivity2));
        threadSafeStateManager.UpdateState();

        // When
        threadSafeStateManager.Clear();

        // Then
        REQUIRE(threadSafeStateManager.Count() == 0);
    }

    TEST_CASE("Clear empty state manager")
    {
        // Given
        ThreadSafeStateManager threadSafeStateManager;

        // When
        threadSafeStateManager.Clear();

        // Then
        REQUIRE(threadSafeStateManager.Count() == 0);
    }
}