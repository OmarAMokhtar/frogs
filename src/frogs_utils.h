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
        bool m_isEnd;
        bool m_isBegin;

    public:
        Iter(T val, T step, bool end = false, bool begin = false)
            : m_val{val}
            , m_step{step}
            , m_isEnd{end}
            , m_isBegin{begin} {}

        Iter(Iter& other)
            : m_val{other.m_val}
            , m_step{other.m_step}
            , m_isEnd{other.m_isEnd}
            , m_isBegin{other.m_isBegin} {}

        Iter(Iter&& other)
            : m_val{other.m_val}
            , m_step{other.m_step}
            , m_isEnd{other.m_isEnd}
            , m_isBegin{other.m_isBegin} {}

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
            m_isBegin = false;
            return *this;
        }

        Iter& operator++(int)
        {
            Iter tmp = *this;
            m_val += m_step;
            m_isBegin = false;
            return tmp;
        }

        T& operator*() { return m_val; }
        T* operator->() { return &m_val; }

        friend bool operator==(Iter a, Iter b)
        {
            if (a.m_isBegin && b.m_val <= a.m_val)
                return true;
            if (b.m_isBegin && a.m_val <= b.m_val)
                return true;
            if (a.m_isEnd && b.m_val >= a.m_val)
                return true;
            if (b.m_isEnd && a.m_val >= b.m_val)
                return true;
            return a.m_val == b.m_val;
        }
        friend bool operator!=(Iter a, Iter b) { return !(a == b); }
    };

    Range::Iter begin() { return {m_min, m_step, false, true}; }
    Range::Iter end() { return {m_max, m_step, true, false}; }

    friend constexpr bool In(T v, Range range)
    {
        auto min = std::min(range.m_max, range.m_min);
        auto max = std::max(range.m_max, range.m_min);
        return (v <= max && v >= min);
    }

    friend constexpr bool Overlap(Range a, Range b)
    {
        if (In(a.m_min, b) || In(a.m_max, b) || In(b.m_min, a) || In(b.m_max, a))
            return true;
        return false;
    }
};

template<typename T>
constexpr T Interpolate(T a, T b, Real ratio)
{
    return a * (1.0-ratio) + b * ratio;
}

} // namespace frogs

#endif // _FROGS_UTILS_H
