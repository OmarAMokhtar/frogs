#ifndef _FROGS_UTILS_H
#define _FROGS_UTILS_H

#include "frogs_primitives.h"

#include <algorithm>

namespace frogs
{

template<typename T>
class Range
{
private:
    T m_min;
    T m_max;
    T m_step;

public:
    Range(T max)
    : m_min{Zero(T{})}
    , m_max{max}
    , m_step{One(T{})}
    {
        if (m_min > m_max)
            m_step = -m_step;
    }

    Range(T min, T max)
    : m_min{min}
    , m_max{max}
    , m_step{One(T{})}
    {
        if (m_min > m_max)
            m_step = -m_step;
    }

    Range(T min, T max, T step)
    : m_min{min}
    , m_max{max}
    , m_step{step} {}

    class Iter
    {
    private:
        T m_val;
        T m_step;

    public:
        Iter(T val, T step) : m_val{val}, m_step{step} {}
        Iter(Iter& other) : m_val{other.m_val}, m_step{other.m_step} {}
        Iter(Iter&& other) : m_val{other.m_val}, m_step{other.m_step} {}
        
        Iter& operator=(Iter&& other)
        {
            m_val = other.m_val;
            m_step = other.m_step;
            return *this;
        }
        
        Iter& operator=(Iter& other)
        {
            m_val = other.m_val;
            m_step = other.m_step;
            return *this;
        }

        Iter& operator++()
        {
            m_val += m_step;
            return *this;
        }

        Iter& operator++(int)
        {
            Iter tmp = *this;
            m_val += m_step;
            return tmp;
        }

        T& operator*() { return m_val; }
        T* operator->() { return &m_val; }

        friend bool operator==(Iter a, Iter b) { return a.m_val == b.m_val; }
        friend bool operator!=(Iter a, Iter b) { return a.m_val != b.m_val; }
    };

    Range::Iter begin() { return {m_min, m_step}; }
    Range::Iter end() { return {m_max, m_step}; }

    friend constexpr bool In(T v, Range range)
    {
        auto min = std::min(range.m_max, range.m_min);
        auto max = std::max(range.m_max, range.m_min);
        return (v <= max && v >= min);
    }
};

template<typename T>
constexpr T Interpolate(T a, T b, Real ratio)
{
    return a * (1.0-ratio) + b * ratio;
}

} // namespace frogs

#endif // _FROGS_UTILS_H
