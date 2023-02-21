#ifndef TREMA_TREMASTANDARDELEMENTSLIBRARY_H
#define TREMA_TREMASTANDARDELEMENTSLIBRARY_H


#include "IElementsLibrary.h"

namespace Trema::View
{
    class TremaStandardElementsLibrary : public IElementsLibrary
    {
    public:
        void AddElements(ViewParser &viewParser) override;

    private:
        void AddBodyElements(ViewParser &viewParser);
        void AddHeadElements(ViewParser &viewParser);
    };
}

#endif //TREMA_TREMASTANDARDELEMENTSLIBRARY_H
