//
// Created by JajaFil on 8/31/2022.
//

#include "OperationsTable.h"

namespace Trema::View
{
    OperationsTable::OperationsTable()
    {
        InsertOperator("+", 1, true, [](std::any a, std::any b) -> std::any
        {
            bool isFirstOperandDouble = a.type() == typeid(double);
            bool isSecondOperandDouble = b.type() == typeid(double);

            if(isFirstOperandDouble && isSecondOperandDouble)
                return std::any_cast<double>(a) + std::any_cast<double>(b);
            else if(isFirstOperandDouble)
                return std::any_cast<double>(a) + std::any_cast<int64_t>(b);
            else if(isSecondOperandDouble)
                return std::any_cast<int64_t>(a) + std::any_cast<double>(b);
            else
                return std::any_cast<int64_t>(a) + std::any_cast<int64_t>(b);
        });

        InsertOperator("-", 1, true, [](std::any a, std::any b) -> std::any
        {
            bool isFirstOperandDouble = a.type() == typeid(double);
            bool isSecondOperandDouble = b.type() == typeid(double);

            if(isFirstOperandDouble && isSecondOperandDouble)
                return std::any_cast<double>(a) - std::any_cast<double>(b);
            else if(isFirstOperandDouble)
                return std::any_cast<double>(a) - std::any_cast<int64_t>(b);
            else if(isSecondOperandDouble)
                return std::any_cast<int64_t>(a) - std::any_cast<double>(b);
            else
                return std::any_cast<int64_t>(a) - std::any_cast<int64_t>(b);
        });

        InsertOperator("*", 2, true, [](std::any a, std::any b) -> std::any
        {
            bool isFirstOperandDouble = a.type() == typeid(double);
            bool isSecondOperandDouble = b.type() == typeid(double);

            if(isFirstOperandDouble && isSecondOperandDouble)
                return std::any_cast<double>(a) * std::any_cast<double>(b);
            else if(isFirstOperandDouble)
                return std::any_cast<double>(a) * std::any_cast<int64_t>(b);
            else if(isSecondOperandDouble)
                return std::any_cast<int64_t>(a) * std::any_cast<double>(b);
            else
                return std::any_cast<int64_t>(a) * std::any_cast<int64_t>(b);
        });

        InsertOperator("/", 2, true, [](std::any a, std::any b) -> std::any
        {
            bool isFirstOperandDouble = a.type() == typeid(double);
            bool isSecondOperandDouble = b.type() == typeid(double);

            if(isFirstOperandDouble && isSecondOperandDouble)
                return std::any_cast<double>(a) / std::any_cast<double>(b);
            else if(isFirstOperandDouble)
                return std::any_cast<double>(a) / std::any_cast<int64_t>(b);
            else if(isSecondOperandDouble)
                return std::any_cast<int64_t>(a) / std::any_cast<double>(b);
            else
                return std::any_cast<int64_t>(a) / std::any_cast<int64_t>(b);
        });

        InsertOperator("%", 2, true, [](std::any a, std::any b) -> std::any
        {
            bool isFirstOperandDouble = a.type() == typeid(double);
            bool isSecondOperandDouble = b.type() == typeid(double);

            if(isFirstOperandDouble && isSecondOperandDouble)
                return ((int64_t) std::any_cast<double>(a)) % ((int64_t) std::any_cast<double>(b));
            else if(isFirstOperandDouble)
                return ((int64_t) std::any_cast<double>(a)) % std::any_cast<int64_t>(b);
            else if(isSecondOperandDouble)
                return std::any_cast<int64_t>(a) % ((int64_t) std::any_cast<double>(b));
            else
                return std::any_cast<int64_t>(a) % std::any_cast<int64_t>(b);
        });


    }

    void OperationsTable::InsertOperator(const std::string& name, int priority, bool leftAssociative,
                                           std::function<std::any(std::any, std::any)> operation)
    {
        OperatorData operatorData
        {
                .Name = name,
                .Priority = priority,
                .IsLeftAssociative = leftAssociative,
                .Operation = std::move(operation)
        };

        m_operators[name] = operatorData;
    }

    const OperatorData& OperationsTable::GetOperator(const std::string &name) const
    {
        return m_operators.at(name);
    }
}