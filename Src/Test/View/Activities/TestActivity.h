//
// Created by Benjam on 10/31/2022.
//

#ifndef TREMA_TESTACTIVITY_H
#define TREMA_TESTACTIVITY_H

#include <memory>
#include <string>
#include <View/Activities/Activity.h>

namespace Trema::Test::View
{
    class TestActivity : public Trema::View::Activity
    {
    public:
        explicit TestActivity(Trema::View::Intent intent, std::shared_ptr<Trema::View::Window> window,
                              uint16_t requestCode = -1) :
                Activity(std::move(intent), std::move(window), requestCode)
        {

        }

        ~TestActivity() override = default;

        std::string GetStringFromIntent(const std::string &name)
        {
            return GetStringExtra(name);
        }

        void OnActivityResult(uint16_t requestCode, uint16_t resultCode, Trema::View::Intent intent) override
        {
            if(OnResultCallback)
                OnResultCallback(requestCode, resultCode, std::move(intent));
        }

        void OnActivityUpdate(double deltaTime) override
        {
            if(OnUpdateCallback)
                OnUpdateCallback(deltaTime);
        }

        std::function<void(uint16_t requestCode, uint16_t resultCode, Trema::View::Intent intent)> OnResultCallback;
        std::function<void(double)> OnUpdateCallback;
    };
}

#endif //TREMA_TESTACTIVITY_H
