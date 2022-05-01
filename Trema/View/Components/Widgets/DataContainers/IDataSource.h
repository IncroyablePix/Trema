//
// Created by JajaFil on 4/30/2022.
//

#ifndef TREMA_PROJECT_IDATASOURCE_H
#define TREMA_PROJECT_IDATASOURCE_H


namespace Trema::View
{
    class IDataSource
    {
    public:

        virtual void Notify() = 0;
    };
}

#endif //TREMA_PROJECT_IDATASOURCE_H
