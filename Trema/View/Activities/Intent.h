//
// Created by JajaFil on 5/21/2022.
//

#ifndef TREMA_PROJECT_INTENT_H
#define TREMA_PROJECT_INTENT_H

#include <string>
#include <unordered_map>
#include <functional>

namespace Trema::View
{
    struct RawIntentValue
    {
        void* Value;
        std::function<void(void)> Free;

        ~RawIntentValue()
        {
            if(Value)
                Free();
        }
    };

    class Intent
    {
    public:
        std::string GetStringExtra(const std::string& name);
        uint64_t GetUint64Extra(const std::string& name);
        uint32_t GetUint32Extra(const std::string& name);
        uint16_t GetUint16Extra(const std::string& name);
         uint8_t GetUint8Extra(const std::string& name);

         int64_t GetInt64Extra(const std::string& name);
         int32_t GetInt32Extra(const std::string& name);
         int16_t GetInt16Extra(const std::string& name);
         int8_t GetInt8Extra(const std::string& name);

         float GetFloatExtra(const std::string& name);
         double GetDoubleExtra(const std::string& name);
         bool GetBoolExtra(const std::string& name);
         char8_t GetCharExtra(const std::string& name);
        
         RawIntentValue GetExtra(const std::string &name);

         void SetStringExtra(const std::string& name, std::string value);
         void SetUint64Extra(const std::string& name, uint64_t value);
         void SetUint32Extra(const std::string& name, uint32_t value);
         void SetUint16Extra(const std::string& name, uint16_t value);
         void SetUint8Extra(const std::string& name, uint8_t value);

         void SetInt64Extra(const std::string& name, int64_t value);
         void SetInt32Extra(const std::string& name, int32_t value);
         void SetInt16Extra(const std::string& name, int16_t value);
         void SetInt8Extra(const std::string& name, int8_t value);

         void SetFloatExtra(const std::string& name, float value);
         void SetDoubleExtra(const std::string& name, double value);
         void SetBoolExtra(const std::string& name, bool value);
         void SetCharExtra(const std::string& name, char value);

         void SetExtra(const std::string& name, RawIntentValue value);

    private:
        std::unordered_map<std::string, std::string> m_strings;
        std::unordered_map<std::string, uint64_t> m_uint64s;
        std::unordered_map<std::string, uint32_t> m_uint32s;
        std::unordered_map<std::string, uint16_t> m_uint16s;
        std::unordered_map<std::string, uint8_t> m_uint8s;
        std::unordered_map<std::string, int64_t> m_int64s;
        std::unordered_map<std::string, int32_t> m_int32s;
        std::unordered_map<std::string, int16_t> m_int16s;
        std::unordered_map<std::string, int8_t> m_int8s;
        std::unordered_map<std::string, float> m_floats;
        std::unordered_map<std::string, double> m_doubles;
        std::unordered_map<std::string, bool> m_bools;
        std::unordered_map<std::string, char> m_chars;
        std::unordered_map<std::string, RawIntentValue> m_rawValues;
    };
}

#endif //TREMA_PROJECT_INTENT_H
