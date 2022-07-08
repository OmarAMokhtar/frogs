#ifndef _FROGS_ANGLE_H
#define _FROGS_ANGLE_H

#include <iostream>
#include <string>
#include <math.h>
#include "frogs_primitives.h"
#include "frogs_constants.h"
#include "frogs_physical_types.h"

namespace frogs
{

class Angle
{
private:
    Real m_value;

public:
    constexpr Angle() : m_value(0.0) {}
    constexpr Angle(Real v) : m_value(v) {}

    using Self = Angle;

    static constexpr Self zero() { return {0.0}; }
    static constexpr Self unit() { return {1.0}; }

    constexpr Self& operator+=(Self a) { m_value += a.m_value; return *this; }
    constexpr Self& operator-=(Self a) { m_value -= a.m_value; return *this; }
    constexpr Self& operator=(Self a) { m_value = a.m_value; return *this; }
    friend constexpr Self operator-(Self a) { return {-a.m_value}; }
    friend constexpr Self operator+(Self a, Self b) { return {a.m_value + b.m_value}; }
    friend constexpr Self operator-(Self a, Self b) { return {a.m_value - b.m_value}; }
    friend constexpr Self operator*(Real a, Self b) { return {a * b.m_value}; }
    friend constexpr Self operator*(Self a, Real b) { return {a.m_value * b}; }
    friend constexpr Self operator/(Self a, Real b) { return {a.m_value / b}; }
    friend constexpr Real operator/(Self a, Self b) { return {a.m_value / b.m_value}; }
    friend constexpr bool operator==(Self a, Self b) { return {a.m_value == b.m_value}; }
    friend constexpr bool operator!=(Self a, Self b) { return {a.m_value != b.m_value}; }
    friend constexpr bool operator>(Self a, Self b) { return {a.m_value > b.m_value}; }
    friend constexpr bool operator>=(Self a, Self b) { return {a.m_value >= b.m_value}; }
    friend constexpr bool operator<(Self a, Self b) { return {a.m_value < b.m_value}; }
    friend constexpr bool operator<=(Self a, Self b) { return {a.m_value <= b.m_value}; }
    friend constexpr Self Abs(Self v) { return (v.m_value < 0) ? -v : v; }
    friend constexpr Real Sqrt(Self v) { return sqrt(v.m_value); }
    friend constexpr Real Cos(Self v) { return cos(v.m_value); }
    friend constexpr Real Sin(Self v) { return sin(v.m_value); }
    friend constexpr Real Tan(Self v) { return tan(v.m_value); }
    friend constexpr Self ACos(Real v) { return {acos(v)}; }
    friend constexpr Self ASin(Real v) { return {asin(v)}; }
    friend constexpr Self ATan(Real v) { return {atan(v)}; }
    friend constexpr Self ATan2(Real a, Real b) { return {atan2(a,b)}; }
    friend constexpr Self ATan2(Distance a, Distance b);
    friend constexpr Self operator""_deg(Integer v);
    friend constexpr Self operator""_deg(Real v);
    friend constexpr Self operator""_rad(Integer v);
    friend constexpr Self operator""_rad(Real v);
    constexpr Real toDegrees() const { return m_value / (convFrom_deg); }
    constexpr Real toRadians() const { return m_value / (convFrom_rad); }

private:
    static constexpr Real convFrom_rad = 1.0;
    static constexpr Real convFrom_deg = PI/180.0;

public:
    str toString()
    {
        str s = std::to_string(m_value);
        s += " rad";
        return s;
    }

    friend std::ostream &operator<<(std::ostream &output, Angle obj)
    {
        output << obj.toString();
        return output;
    }
};

constexpr Angle operator""_deg(Integer v) { return {v * (Angle::convFrom_deg)}; }
constexpr Angle operator""_deg(Real v) { return {v * (Angle::convFrom_deg)}; }
constexpr Angle operator""_rad(Integer v) { return {v * (Angle::convFrom_rad)}; }
constexpr Angle operator""_rad(Real v) { return {v * (Angle::convFrom_rad)}; }

constexpr Angle ATan2(Distance a, Distance b) { return {atan2(a.toMeters(), b.toMeters())}; }

}

#endif // _FROGS_ANGLE_H
