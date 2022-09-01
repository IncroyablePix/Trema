//
// Created by JajaFil on 8/31/2022.
//

#ifndef TREMA_PROJECT_OPERATIONSTABLE_H
#define TREMA_PROJECT_OPERATIONSTABLE_H

#include <string>
#include <functional>
#include <any>

namespace Trema::View
{
    struct OperatorData
    {
        std::string Name;
        int Priority;
        bool IsLeftAssociative;
        std::function<std::any(std::any, std::any)> Operation;
    };

    class OperationsTable
    {
    public:
        OperationsTable();
        OperationsTable(const OperationsTable& st) = delete;
        OperationsTable& operator=(const OperationsTable&) = delete;

        void InsertOperator(const std::string& name, int priority, bool leftAssociative, std::function<std::any(std::any, std::any)> operation);
        const OperatorData& GetOperator(const std::string& name) const;
    private:
        std::unordered_map<std::string, OperatorData> m_operators;
    };
}


#endif //TREMA_PROJECT_OPERATIONSTABLE_H
