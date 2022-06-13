//
// Created by JajaFil on 5/21/2022.
//

#include "Intent.h"

namespace Trema::View
{
    std::string Intent::GetStringExtra(const std::string &name)
    {
        if(m_strings.contains(name))
            return std::move(m_strings.at(name));

        return "";
    }

    uint64_t Intent::GetUint64Extra(const std::string &name)
    {
        if(m_uint64s.contains(name))
            return m_uint64s.at(name);

        return 0;
    }

    uint32_t Intent::GetUint32Extra(const std::string &name)
    {
        if(m_uint32s.contains(name))
            return m_uint32s.at(name);

        return 0;
    }

    uint16_t Intent::GetUint16Extra(const std::string &name)
    {
        if(m_uint16s.contains(name))
            return m_uint16s.at(name);

        return 0;
    }

    uint8_t Intent::GetUint8Extra(const std::string &name)
    {
        if(m_uint8s.contains(name))
            return m_uint8s.at(name);

        return 0;
    }

    int64_t Intent::GetInt64Extra(const std::string &name)
    {
        if(m_int64s.contains(name))
            return m_int64s.at(name);

        return 0;
    }

    int32_t Intent::GetInt32Extra(const std::string &name)
    {
        if(m_int32s.contains(name))
            return m_int32s.at(name);

        return 0;
    }

    int16_t Intent::GetInt16Extra(const std::string &name)
    {
        if(m_int16s.contains(name))
            return m_int16s.at(name);

        return 0;
    }

    int8_t Intent::GetInt8Extra(const std::string &name)
    {
        if(m_int8s.contains(name))
            return m_int8s.at(name);

        return 0;
    }

    float Intent::GetFloatExtra(const std::string &name)
    {
        if(m_floats.contains(name))
            return m_floats.at(name);

        return 0;
    }

    double Intent::GetDoubleExtra(const std::string &name)
    {
        if(m_doubles.contains(name))
            return m_doubles.at(name);

        return 0;
    }

    bool Intent::GetBoolExtra(const std::string &name)
    {
        if(m_bools.contains(name))
            return m_bools.at(name);

        return false;
    }

    char8_t Intent::GetCharExtra(const std::string &name)
    {
        if(m_chars.contains(name))
            return m_chars.at(name);

        return '\0';
    }

    RawIntentValue Intent::GetExtra(const std::string &name)
    {
        if(m_rawValues.contains(name))
            return m_rawValues.at(name);

        return { nullptr, [](){ /* Should free the pointer */} };
    }

    void Intent::SetStringExtra(const std::string &name, std::string value)
    {
        m_strings[name] = std::move(value);
    }

    void Intent::SetUint64Extra(const std::string &name, uint64_t value)
    {
        m_uint64s[name] = value;
    }

    void Intent::SetUint32Extra(const std::string &name, uint32_t value)
    {
        m_uint32s[name] = value;
    }

    void Intent::SetUint16Extra(const std::string &name, uint16_t value)
    {
        m_uint16s[name] = value;
    }

    void Intent::SetUint8Extra(const std::string &name, uint8_t value)
    {
        m_uint8s[name] = value;
    }

    void Intent::SetInt64Extra(const std::string &name, int64_t value)
    {
        m_int64s[name] = value;
    }

    void Intent::SetInt32Extra(const std::string &name, int32_t value)
    {
        m_int32s[name] = value;
    }

    void Intent::SetInt16Extra(const std::string &name, int16_t value)
    {
        m_int16s[name] = value;
    }

    void Intent::SetInt8Extra(const std::string &name, int8_t value)
    {
        m_int8s[name] = value;
    }

    void Intent::SetFloatExtra(const std::string &name, float value)
    {
        m_floats[name] = value;
    }

    void Intent::SetDoubleExtra(const std::string &name, double value)
    {
        m_doubles[name] = value;
    }

    void Intent::SetBoolExtra(const std::string &name, bool value)
    {
        m_bools[name] = value;
    }

    void Intent::SetCharExtra(const std::string &name, char value)
    {
        m_chars[name] = value;
    }

    void Intent::SetExtra(const std::string &name, RawIntentValue value)
    {
        m_rawValues[name] = std::move(value);
    }
}
