//
// Created by Benjam on 11/8/2022.
//

#ifndef TREMA_MISTAKESCONTAINER_H
#define TREMA_MISTAKESCONTAINER_H

#include <deque>
#include "CompilationMistake.h"

namespace Trema::View
{
    class MistakesContainer
    {
    public:
        MistakesContainer();
        void Clear();
        inline size_t Size() const { return m_mistakes.size(); }
        inline bool Empty() const { return m_mistakes.empty(); }
        MistakesContainer& operator<<(CompilationMistake mistake);
        friend std::ostream& operator<<(std::ostream& os, const MistakesContainer& mistakes);
        CompilationMistake& operator[](int idx);

    private:
        std::deque<CompilationMistake> m_mistakes;
    };
}

#endif //TREMA_MISTAKESCONTAINER_H
