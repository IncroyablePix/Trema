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
    template<typename T, typename C> requires IsCollection<C>
    class ObservableCollection
    {
    public:
        virtual ~ObservableCollection() = default;
        virtual void Subscribe(std::function<void(const ObservableCollection& collection)> callback) = 0;
        virtual void Notify() = 0;

    protected:
        typedef T ObservableContainer;
        ObservableContainer m_data;

    public:
        typedef typename ObservableContainer::iterator iterator;
        typedef typename ObservableContainer::const_iterator const_iterator;

        inline iterator begin() { return m_data.begin(); }
        inline const_iterator begin() const { return m_data.begin(); }
        inline iterator end() { return m_data.end(); }
        inline const_iterator end() const { return m_data.end(); }
    };
}

#endif //TREMA_PROJECT_OBSERVABLECOLLECTION_H
