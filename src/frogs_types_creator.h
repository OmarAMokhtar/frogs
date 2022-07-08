#ifndef _FROGS_TYPES_CREATOR_H
#define _FROGS_TYPES_CREATOR_H

#include <cstdint>
#include <iostream>
#include <string>

#include "frogs_primitives.h"

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
public: \
    constexpr ClassName() : m_value(0.0) {} \
    constexpr ClassName(Real v) : m_value(v) {} \
    using Self = ClassName; \
    static constexpr Self zero() { return {0.0}; } \
    static constexpr Self unit() { return {1.0}; } \
    constexpr Self& operator+=(Self a) { m_value += a.m_value; return *this; } \
    constexpr Self& operator-=(Self a) { m_value -= a.m_value; return *this; } \
    constexpr Self& operator*=(Real a) { m_value *= a; return *this; } \
    constexpr Self& operator/=(Real a) { m_value *= a; return *this; } \
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
    friend constexpr Self Abs(Self v) { return Abs(v); } \
    template<typename T> friend constexpr auto Diff(T); \
    Str toString() { \
        Str s = std::to_string(m_value); \
        s += " " #String; \
        return s; \
    } \
    PublicDecl \
    friend std::ostream &operator<<(std::ostream &output, ClassName obj) { \
        output << obj.toString(); \
        return output; \
    } \
};

#define DECL_FWD(ClassName) \
class ClassName; \

#endif // _FROGS_TYPES_CREATOR_H
