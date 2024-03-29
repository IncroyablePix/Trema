#ifndef TREMA_STACKSPACE_H
#define TREMA_STACKSPACE_H

#include <vector>
#include "../Layout.h"
#include "../../Container/Container.h"

namespace Trema::View
{
    class StackSpace : public Layout
    {
    public:
        explicit StackSpace(std::string title);
        StackSpace(const StackSpace&) = delete;
        StackSpace& operator=(const StackSpace&) = delete;
        ~StackSpace() override = default;

        void Show() override;
        void AddContainer(std::shared_ptr<Container> container, std::unordered_map<std::string, std::string> &attributes) override;

        static std::shared_ptr<StackSpace> CreateStackSpace(std::string title);

    private:
        void Begin();
        void End();
        std::vector<std::shared_ptr<Container>> m_elements;
    };
}

#endif //TREMA_STACKSPACE_H
