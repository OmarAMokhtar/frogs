#ifndef _FROGS_PHYSICAL_TYPES_H
#define _FROGS_PHYSICAL_TYPES_H

#include <cstdint>
#include <iostream>
#include <string>

namespace frogs
{

/* The primitive types */

using Integer = unsigned long long;
using Real = long double;

/* The macros that helps build classes */

#define DECL_UNIT(P, Unit, Getter, Scale) \
    friend constexpr Self operator""##Unit(Integer v); \
    friend constexpr Self operator""##Unit(Real v); \
    private: static constexpr Real convFrom##Unit = Scale; \
    public: constexpr Real Getter() const { return m_value / (convFrom##Unit); } \

#define IMPL_UNIT(ClassName, Unit) \
    constexpr ClassName operator""##Unit(Integer v) { return {v * (ClassName::convFrom##Unit)}; } \
    constexpr ClassName operator""##Unit(Real v) { return {v * (ClassName::convFrom##Unit)}; } \

#define DECL_CONV(Result, ClassA, Opr, ClassB) \
    friend constexpr Result operator Opr(ClassA a, ClassB b); \

#define IMPL_CONV(Result, ClassA, UnitA, Opr, ClassB, UnitB) \
    constexpr Result operator Opr(ClassA a, ClassB b) { return {a.UnitA() Opr b.UnitB()}; } \

#define DECL_CONV_ADD(Result, ClassA, ClassB) \
    DECL_CONV(Result, ClassA, +, ClassB) \
    DECL_CONV(Result, ClassB, +, ClassA)

#define IMPL_CONV_ADD(Result, ClassA, UnitA, ClassB, UnitB) \
    IMPL_CONV(Result, ClassA, UnitA, +, ClassB, UnitB) \
    IMPL_CONV(Result, ClassB, UnitB, +, ClassA, UnitA)

#define DECL_CONV_SUB(Result, ClassA, ClassB) \
    DECL_CONV(Result, ClassA, -, ClassB) \
    DECL_CONV(Result, ClassB, -, ClassA)

#define IMPL_CONV_SUB(Result, ClassA, UnitA, ClassB, UnitB) \
    IMPL_CONV(Result, ClassA, UnitA, -, ClassB, UnitB) \
    IMPL_CONV(Result, ClassB, UnitB, -, ClassA, UnitA)

#define DECL_CONV_MUL(Result, ClassA, ClassB) \
    DECL_CONV(Result, ClassA, *, ClassB) \
    DECL_CONV(Result, ClassB, *, ClassA) \

#define IMPL_CONV_MUL(Result, ClassA, UnitA, ClassB, UnitB) \
    IMPL_CONV(Result, ClassA, UnitA, *, ClassB, UnitB) \
    IMPL_CONV(Result, ClassB, UnitB, *, ClassA, UnitA) \

#define DECL_CONV_SQR(Result, Class) \
    DECL_CONV(Result, Class, *, Class) \

#define IMPL_CONV_SQR(Result, Class, Unit) \
    IMPL_CONV(Result, Class, Unit, *, Class, Unit) \

#define DECL_CONV_DIV(Result, ClassA, ClassB) \
    DECL_CONV(Result, ClassA, /, ClassB)

#define IMPL_CONV_DIV(Result, ClassA, UnitA, ClassB, UnitB) \
    IMPL_CONV(Result, ClassA, UnitA, /, ClassB, UnitB)

#define DECL_CLASS(ClassName, String, PublicDecl) \
class ClassName { \
private: \
    Real m_value; \
    constexpr ClassName() : m_value(0.0) {} \
    constexpr ClassName(Real v) : m_value(v) {} \
public: \
    using Self = ClassName; \
    constexpr Self& operator+=(Self a) { m_value += a.m_value; return *this; } \
    constexpr Self& operator-=(Self a) { m_value -= a.m_value; return *this; } \
    constexpr Self& operator=(Self a) { m_value = a.m_value; return *this; } \
    friend constexpr Self operator-(Self a) { return {-a.m_value}; } \
    friend constexpr Self operator+(Self a, Self b) { return {a.m_value + b.m_value}; } \
    friend constexpr Self operator-(Self a, Self b) { return {a.m_value - b.m_value}; } \
    friend constexpr Self operator*(Real a, Self b) { return {a * b.m_value}; } \
    friend constexpr Self operator*(Self a, Real b) { return {a.m_value * b}; } \
    friend constexpr Self operator/(Self a, Real b) { return {a.m_value / b}; } \
    friend constexpr Real operator/(Self a, Self b) { return {a.m_value / b.m_value}; } \
    friend constexpr bool operator==(Self a, Self b) { return {a.m_value == b.m_value}; } \
    friend constexpr bool operator!=(Self a, Self b) { return {a.m_value != b.m_value}; } \
    friend constexpr bool operator>(Self a, Self b) { return {a.m_value > b.m_value}; } \
    friend constexpr bool operator>=(Self a, Self b) { return {a.m_value >= b.m_value}; } \
    friend constexpr bool operator<(Self a, Self b) { return {a.m_value < b.m_value}; } \
    friend constexpr bool operator<=(Self a, Self b) { return {a.m_value <= b.m_value}; } \
    PublicDecl \
    friend std::ostream &operator<<(std::ostream &output, ClassName obj) { \
        output << obj.m_value << " " << #String; \
        return output; \
    } \
};

#define DECL_FWD(ClassName) \
class ClassName; \

/* All forward declarations */

DECL_FWD(Distance)
DECL_FWD(Time)
DECL_FWD(Velocity)
DECL_FWD(Acceleration)
DECL_FWD(Mass)
DECL_FWD(Force)
DECL_FWD(Area)

/* All class definitions */

DECL_CLASS( Distance,
            meters,
            DECL_UNIT(Distance, _m,     toMeters,       1.0)
            DECL_UNIT(Distance, _cm,    toCentimeters,  1.0e-2)
            DECL_UNIT(Distance, _mm,    toMillimeters,  1.0e-3)
            DECL_UNIT(Distance, _um,    toMicrometers,  1.0e-6)
            DECL_UNIT(Distance, _nm,    toNanometers,   1.0e-9)
            DECL_UNIT(Distance, _km,    toKilometers,   1.0e+3)
            DECL_UNIT(Distance, _inch,  toInches,       0.0254)
            DECL_UNIT(Distance, _ft,    toFeet,         0.3048)
            DECL_UNIT(Distance, _miles, toMiles,        1609.344)
            DECL_CONV_DIV(Distance, Area, Distance) )

DECL_CLASS( Time,
            seconds,
            DECL_UNIT(Time, _hours,   toHours,         3600.0)
            DECL_UNIT(Time, _minutes, toMinutes,       60.0)
            DECL_UNIT(Time, _sec,     toSeconds,       1.0e+0)
            DECL_UNIT(Time, _msec,    toMilliseconds,  1.0e-3)
            DECL_UNIT(Time, _usec,    toMicroseconds,  1.0e-6)
            DECL_UNIT(Time, _nsec,    toNanoseconds,   1.0e-9) )

DECL_CLASS( Velocity,
            m/s,
            DECL_UNIT(Velocity, _kmph, toKilometersPerHour,  1.0/3.6)
            DECL_UNIT(Velocity, _mph,  toMilesPerHour,       0.44704)
            DECL_UNIT(Velocity, _mps,  toMetersPerSecond,    1.0e+0)
            DECL_CONV_DIV(Velocity, Distance, Time) )

DECL_CLASS( Acceleration,
            m/s2,
            DECL_UNIT(Acceleration, _mps2,  toMetersPerSecond2,      1.0e+0)
            DECL_UNIT(Acceleration, _mmps2, toMillimetersPerSecond2, 1.0e-3)
            DECL_UNIT(Acceleration, _umps2, toMicrometersPerSecond2, 1.0e-6)
            DECL_UNIT(Acceleration, _nmps2, toNanometersPerSecond2,  1.0e-9)
            DECL_CONV_DIV(Acceleration, Velocity, Time) )

DECL_CLASS( Mass,
            kg,
            DECL_UNIT(Mass, _kg, toKilograms,  1.0e+3)
            DECL_UNIT(Mass, _g,  toGrams,      1.0e+0)
            DECL_UNIT(Mass, _mg, toMilligrams, 1.0e-3)
            DECL_UNIT(Mass, _ug, toMicrograms, 1.0e-6)
            DECL_UNIT(Mass, _ng, toNanograms,  1.0e-9)
            DECL_UNIT(Mass, _lb, toPounds,     453.59)
            DECL_UNIT(Mass, _oz, toOunces,     28.350) )

DECL_CLASS( Force,
            N,
            DECL_UNIT(Force, _N, toNewtons, 1.0e+0)
            DECL_CONV_MUL(Force, Mass, Acceleration) )

DECL_CLASS( Area,
            m2,
            DECL_UNIT(Area, _km2, toKilometers2,  1.0e+6)
            DECL_UNIT(Area, _m2,  toMeters2,      1.0e+0)
            DECL_UNIT(Area, _cm2, toCentimeters2, 1.0e-4)
            DECL_UNIT(Area, _mm2, toMillimeters2, 1.0e-6)
            DECL_UNIT(Area, _um2, toMicrometers2, 1.0e-12)
            DECL_UNIT(Area, _nm2, toNanometers2,  1.0e-18)
            DECL_CONV_SQR(Area, Distance) )

DECL_CLASS( Energy,
            J,
            DECL_UNIT(Energy, _J,    toJoules,       1.0e+0)
            DECL_UNIT(Energy, _kJ,   toKilojoules,   1.0e+3)
            DECL_UNIT(Energy, _MJ,   toMegajoules,   1.0e+6)
            DECL_UNIT(Energy, _GJ,   toGigajoules,   1.0e+9)
            DECL_UNIT(Energy, _mJ,   toMillijoules,  1.0e-3)
            DECL_UNIT(Energy, _uJ,   toMicrojoules,  1.0e-6)
            DECL_UNIT(Energy, _nJ,   toNanojoules,   1.0e-9)
            DECL_UNIT(Energy, _kWh,  toKilowattHour, 3.6e+6)
            DECL_UNIT(Energy, _cal,  toCalories,     4.184e+0)
            DECL_UNIT(Energy, _kcal, toKilocalories, 4.184e+3) )

/* All implementations */

IMPL_UNIT(Distance, _m)
IMPL_UNIT(Distance, _cm)
IMPL_UNIT(Distance, _mm)
IMPL_UNIT(Distance, _um)
IMPL_UNIT(Distance, _nm)
IMPL_UNIT(Distance, _km)
IMPL_UNIT(Distance, _inch)
IMPL_UNIT(Distance, _ft)
IMPL_UNIT(Distance, _miles)
IMPL_CONV_DIV(Distance, Area, toMeters2, Distance, toMeters)

IMPL_UNIT(Time, _hours)
IMPL_UNIT(Time, _minutes)
IMPL_UNIT(Time, _sec)
IMPL_UNIT(Time, _msec)
IMPL_UNIT(Time, _usec)
IMPL_UNIT(Time, _nsec)

IMPL_UNIT(Velocity, _kmph)
IMPL_UNIT(Velocity, _mph)
IMPL_UNIT(Velocity, _mps)
IMPL_CONV_DIV(Velocity, Distance, toMeters, Time, toSeconds)
            
IMPL_UNIT(Acceleration, _mps2)
IMPL_UNIT(Acceleration, _mmps2)
IMPL_UNIT(Acceleration, _umps2)
IMPL_UNIT(Acceleration, _nmps2)
IMPL_CONV_DIV(Acceleration, Velocity, toMetersPerSecond, Time, toSeconds)

IMPL_UNIT(Mass, _kg)
IMPL_UNIT(Mass, _g)
IMPL_UNIT(Mass, _mg)
IMPL_UNIT(Mass, _ug)
IMPL_UNIT(Mass, _ng)
IMPL_UNIT(Mass, _lb)
IMPL_UNIT(Mass, _oz)

IMPL_UNIT(Area, _km2)
IMPL_UNIT(Area, _m2)
IMPL_UNIT(Area, _cm2)
IMPL_UNIT(Area, _mm2)
IMPL_UNIT(Area, _um2)
IMPL_UNIT(Area, _nm2)
IMPL_CONV_SQR(Area, Distance, toMeters)

} // namespace frogs

#endif // _FROGS_PHYSICAL_TYPES_H
