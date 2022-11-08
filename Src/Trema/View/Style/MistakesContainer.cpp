//
// Created by Benjam on 11/8/2022.
//

#include "MistakesContainer.h"

namespace Trema::View
{
    MistakesContainer::MistakesContainer()
    = default;

    void MistakesContainer::Clear()
    {
        m_mistakes.clear();
    }

    MistakesContainer &MistakesContainer::operator<<(CompilationMistake mistake)
    {
        m_mistakes.push_back(std::move(mistake));
        return *this;
    }

    std::ostream &operator<<(std::ostream &os, const MistakesContainer &mistakes)
    {
        for(const auto& mistake : mistakes.m_mistakes)
        {
            os << mistake;
        }
        return os;
    }

    CompilationMistake &MistakesContainer::operator[](int idx)
    {
        return m_mistakes[idx];
    }
}