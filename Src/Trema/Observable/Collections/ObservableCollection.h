//
// Created by Benjam on 10/3/2022.
//

#ifndef TREMA_PROJECT_OBSERVABLECOLLECTION_H
#define TREMA_PROJECT_OBSERVABLECOLLECTION_H

#include <functional>
#include <vector>
#include "IsCollection.h"

namespace Trema::Observable
{
    template<typename C> requires IsCollection<C>
    class ObservableCollection : public std::enable_shared_from_this<ObservableCollection<C>>
    {
    public:
        ObservableCollection()
        = default;

        explicit ObservableCollection(C collection) : m_data(std::move(collection))
        {

        }

        virtual ~ObservableCollection() = default;
        virtual void Subscribe(std::string name, std::function<void(const ObservableCollection& collection)> callback)
        {
            m_callbacks[std::move(name)] = std::move(callback);
        }

        void Notify() const
        {
            for(const auto& [name, function] : m_callbacks)
            {
                function(*this);
            }
        }

        typedef C ObservableContainer;
        typedef typename ObservableContainer::iterator iterator;
        typedef typename ObservableContainer::const_iterator const_iterator;

        inline iterator begin() { return m_data.begin(); }
        inline const_iterator begin() const { return m_data.begin(); }
        inline iterator end() { return m_data.end(); }
        inline const_iterator end() const { return m_data.end(); }
        inline ObservableContainer& GetContainer() { return (std::vector<std::basic_string<char>> &) m_data; }

    protected:
        const ObservableContainer m_data;

    private:
        std::unordered_map<std::string, std::function<void(const ObservableCollection& collection)>> m_callbacks;

    };
}

#endif //TREMA_PROJECT_OBSERVABLECOLLECTION_H
