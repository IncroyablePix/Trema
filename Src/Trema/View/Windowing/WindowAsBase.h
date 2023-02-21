#ifndef TREMA_PROJECT_WINDOWASBASE_H
#define TREMA_PROJECT_WINDOWASBASE_H

#include <memory>

namespace Trema::View
{
    class Window;

    template<class T>
    concept WindowAsBase = std::is_base_of_v<Window, T>;
}

#endif //TREMA_PROJECT_WINDOWASBASE_H
