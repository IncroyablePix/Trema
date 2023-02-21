#ifndef TREMA_PROJECT_DATASOURCE_H
#define TREMA_PROJECT_DATASOURCE_H

#include <string>
#include <memory>
#include <unordered_map>
#include "IDataConsumer.h"

namespace Trema::View
{
    class DataSource
    {
    public:
        virtual void Notify() = 0;
        void RegisterListener(std::string elementName, std::shared_ptr<IDataConsumer> consumer);

    private:
        std::unordered_map<std::string, std::shared_ptr<IDataConsumer>> m_consumers;
    };
}

#endif //TREMA_PROJECT_DATASOURCE_H
