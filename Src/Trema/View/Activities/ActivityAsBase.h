#ifndef TREMA_PROJECT_ACTIVITYASBASE_H
#define TREMA_PROJECT_ACTIVITYASBASE_H

#include <memory>

namespace Trema::View
{
    class Activity;

    template<class T>
    concept ActivityAsBase = std::is_base_of_v<Activity, T>;

    // as a replacement for:
    // template<class T, class = std::enable_if_t<std::is_base_of_v<Activity, T>>>
}
#endif //TREMA_PROJECT_ACTIVITYASBASE_H
