//
// Created by JajaFil on 3/29/2022.
//

#ifndef TREMA_STACKSPACE_H
#define TREMA_STACKSPACE_H

#include <vector>
#include "../ILayout.h"
#include "../../Container/IContainer.h"

namespace Trema::View
{
    class StackSpace : public ILayout
    {
    public:
        explicit StackSpace(std::string title);
        ~StackSpace();
        void Show() override;
        void AddContainer(std::shared_ptr<IContainer> container, std::unordered_map<std::string, std::string> &attributes, const std::shared_ptr<Window> &window) override;

        static std::shared_ptr<StackSpace> CreateStackSpace(std::string title);

    private:
        void Begin();
        void End();
        std::vector<std::shared_ptr<IContainer>> m_elements;
    };
}

#endif //TREMA_STACKSPACE_H
