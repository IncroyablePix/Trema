#include "DataSource.h"

namespace Trema::View
{
    void DataSource::RegisterListener(std::string elementName, std::shared_ptr<IDataConsumer> consumer)
    {
        m_consumers[std::move(elementName)] = std::move(consumer);
    }
}