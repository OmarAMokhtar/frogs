#ifndef _FROGS_TYPES_CREATOR_H
#define _FROGS_TYPES_CREATOR_H

#include <cstdint>
#include <iostream>
#include <string>

#include "frogs_primitives.h"

/* The macros that helps build classes */

#define DECL_UNIT(Result, Unit, Getter, Scale) \
    static constexpr Real convFrom##Unit = Scale; \
    constexpr Real Getter() const { return m_value / (convFrom##Unit); } \

#define IMPL_UNIT(ClassName, Unit) \
    constexpr ClassName operator""##Unit(unsigned long long v) { return {v * (ClassName::convFrom##Unit)}; } \
    constexpr ClassName operator""##Unit(long double v) { return {static_cast<Real>(v) * (ClassName::convFrom##Unit)}; } \

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

#define DECL_CONV_AB_DIV_C(Result, ClassA, ClassB, ClassC) \
    friend constexpr Result operator/(UnitsMul<ClassA,ClassB,0>, ClassC); \
    friend constexpr Result operator/(UnitsMul<ClassB,ClassA,0>, ClassC); \
    friend constexpr Result operator*(ClassA, UnitsDiv<ClassB,ClassC,0>); \
    friend constexpr Result operator*(ClassB, UnitsDiv<ClassA,ClassC,0>); \
    friend constexpr Result operator*(UnitsDiv<ClassB,ClassC,0>, ClassA); \
    friend constexpr Result operator*(UnitsDiv<ClassA,ClassC,0>, ClassB);

#define IMPL_CONV_AB_DIV_C(Result, ClassA, UnitA, ClassB, UnitB, ClassC, UnitC) \
    constexpr Result operator/(UnitsMul<ClassA,ClassB,0> ab, ClassC c) \
    { return {(ab.m_a.UnitA() * ab.m_b.UnitB()) / c.UnitC()}; } \
    constexpr Result operator/(UnitsMul<ClassB,ClassA,0> ab, ClassC c) \
    { return {(ab.m_a.UnitB() * ab.m_b.UnitA()) / c.UnitC()}; } \
    constexpr Result operator*(ClassA a, UnitsDiv<ClassB,ClassC,0> b_c) \
    { return {a.UnitA() * (b_c.m_a.UnitB() / b_c.m_b.UnitC())}; } \
    constexpr Result operator*(ClassB b, UnitsDiv<ClassA,ClassC,0> a_c) \
    { return {b.UnitB() * (a_c.m_a.UnitA() / a_c.m_b.UnitC())}; } \
    constexpr Result operator*(UnitsDiv<ClassB,ClassC,0> b_c, ClassA a) \
    { return {(b_c.m_a.UnitB() / b_c.m_b.UnitC()) * a.UnitA()}; } \
    constexpr Result operator*(UnitsDiv<ClassA,ClassC,0> a_c, ClassB b) \
    { return {(a_c.m_a.UnitA() / a_c.m_b.UnitC()) * b.UnitB()}; }

// #define DECL_CONV_A_DIV_BC(Result, ClassA, ClassB, ClassC) \
//     friend constexpr Result operator/(UnitsMul<ClassA,ClassB,0>, ClassC); \
//     friend constexpr Result operator/(UnitsMul<ClassB,ClassA,0>, ClassC); \
//     friend constexpr Result operator*(ClassA, UnitsDiv<ClassB,ClassC,0>); \
//     friend constexpr Result operator*(ClassB, UnitsDiv<ClassA,ClassC,0>); \
//     friend constexpr Result operator*(UnitsDiv<ClassB,ClassC,0>, ClassA); \
//     friend constexpr Result operator*(UnitsDiv<ClassA,ClassC,0>, ClassB);

#define DECL_CLASS(ClassName, String, PublicDecl) \
template<int P = 1> \
class ClassName##T { \
private: \
    Real m_value; \
public: \
    constexpr ClassName##T() : m_value(0.0) {} \
    constexpr ClassName##T(Real v) : m_value(v) {} \
    using Self = ClassName##T<P>; \
    static constexpr Self zero() { return {0.0}; } \
    static constexpr Self unit() { return {1.0}; } \
    constexpr Self& operator+=(Self a) { m_value += a.m_value; return *this; } \
    constexpr Self& operator-=(Self a) { m_value -= a.m_value; return *this; } \
    constexpr Self& operator*=(Real a) { m_value *= a; return *this; } \
    constexpr Self& operator/=(Real a) { m_value *= a; return *this; } \
    constexpr Self& operator=(Self a) { m_value = a.m_value; return *this; } \
    constexpr auto operator,(Self other) { return Vec2{*this, other}; } \
    constexpr auto operator,(Vec2<Self> other) { return Vec3{*this, other}; } \
    constexpr auto operator,(Vec3<Self> other) { return Vec4{*this, other}; } \
    template<int N> friend constexpr ClassName##T<N> operator-(ClassName##T<N> a); \
    template<int N> friend constexpr ClassName##T<N> operator+(ClassName##T<N> a); \
    template<int N> friend constexpr ClassName##T<N> operator+(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr ClassName##T<N> operator-(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr ClassName##T<N> operator*(Real a, ClassName##T<N> b); \
    template<int N> friend constexpr ClassName##T<N> operator*(ClassName##T<N> a, Real b); \
    template<int N> friend constexpr ClassName##T<N> operator/(ClassName##T<N> a, Real b); \
    template<int N> friend constexpr ClassName##T<-N> operator/(Real a, ClassName##T<N> b); \
    template<int N, int M> friend constexpr ClassName##T<N+M> operator*(ClassName##T<N> a, ClassName##T<M> b); \
    template<int N, int M> friend constexpr ClassName##T<N-M> operator/(ClassName##T<N> a, ClassName##T<M> b); \
    template<int N> friend constexpr Real operator/(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr bool operator==(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr bool operator!=(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr bool operator>(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr bool operator>=(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr bool operator<(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr bool operator<=(ClassName##T<N> a, ClassName##T<N> b); \
    template<int N> friend constexpr ClassName##T<N> Abs(ClassName##T<N> v); \
    friend constexpr ClassName##T<1> Sqrt(ClassName##T<2> v); \
    friend constexpr ClassName##T<2> Sqrt(ClassName##T<4> v); \
    friend constexpr ClassName##T<3> Sqrt(ClassName##T<6> v); \
    friend constexpr ClassName##T<4> Sqrt(ClassName##T<8> v); \
    template<int N> friend constexpr ClassName##T<N*2> Sqr(ClassName##T<N> v); \
    template<int N> friend constexpr ClassName##T<N*3> Cube(ClassName##T<N> v); \
    template<typename T> friend constexpr auto Diff(T); \
    Str toString() const { \
        return conv2str(m_value) + " " #String \
        + ((P != 1) ? conv2str(P) : Str("")); } \
    PublicDecl \
    friend std::ostream &operator<<(std::ostream &output, const ClassName##T obj) { \
        output << obj.toString(); \
        return output; \
    } \
    template <int N> friend constexpr ClassName##T<N> One(ClassName##T<N>&); \
    template <int N> friend constexpr ClassName##T<N> One(ClassName##T<N>&&); \
    template <int N> friend constexpr ClassName##T<N> Zero(ClassName##T<N>&); \
    template <int N> friend constexpr ClassName##T<N> Zero(ClassName##T<N>&&); \
};

#define IMPL_CLASS(ClassName) \
    template<int N> constexpr ClassName##T<N> operator-(ClassName##T<N> a) { return {-a.m_value}; } \
    template<int N> constexpr ClassName##T<N> operator+(ClassName##T<N> a) { return a; } \
    template<int N> constexpr ClassName##T<N> operator+(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value + b.m_value}; } \
    template<int N> constexpr ClassName##T<N> operator-(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value - b.m_value}; } \
    template<int N> constexpr ClassName##T<N> operator*(Real a, ClassName##T<N> b) { return {a * b.m_value}; } \
    template<int N> constexpr ClassName##T<N> operator*(ClassName##T<N> a, Real b) { return {a.m_value * b}; } \
    template<int N> constexpr ClassName##T<N> operator/(ClassName##T<N> a, Real b) { return {a.m_value / b}; } \
    template<int N> constexpr ClassName##T<-N> operator/(Real a, ClassName##T<N> b) { return {a / b.m_value}; } \
    template<int N, int M> \
    constexpr ClassName##T<N+M> operator*(ClassName##T<N> a, ClassName##T<M> b) \
    { return {a.m_value * b.m_value}; } \
    template<int N, int M> \
    constexpr ClassName##T<N-M> operator/(ClassName##T<N> a, ClassName##T<M> b) \
    { return {a.m_value / b.m_value}; } \
    template<int N> constexpr Real operator/(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value / b.m_value}; } \
    template<int N> constexpr bool operator==(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value == b.m_value}; } \
    template<int N> constexpr bool operator!=(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value != b.m_value}; } \
    template<int N> constexpr bool operator>(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value > b.m_value}; } \
    template<int N> constexpr bool operator>=(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value >= b.m_value}; } \
    template<int N> constexpr bool operator<(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value < b.m_value}; } \
    template<int N> constexpr bool operator<=(ClassName##T<N> a, ClassName##T<N> b) { return {a.m_value <= b.m_value}; } \
    template<int N> constexpr ClassName##T<N> Abs(ClassName##T<N> v) { return (v.m_value < 0) ? -v : v; } \
    constexpr ClassName##T<1> Sqrt(ClassName##T<2> v) { return {sqrt(v.m_value)}; } \
    constexpr ClassName##T<2> Sqrt(ClassName##T<4> v) { return {sqrt(v.m_value)}; } \
    constexpr ClassName##T<3> Sqrt(ClassName##T<6> v) { return {sqrt(v.m_value)}; } \
    constexpr ClassName##T<4> Sqrt(ClassName##T<8> v) { return {sqrt(v.m_value)}; } \
    template<int N> constexpr ClassName##T<N*2> Sqr(ClassName##T<N> v) { return {v.m_value*v.m_value}; } \
    template<int N> constexpr ClassName##T<N*3> Cube(ClassName##T<N> v) { return {v.m_value*v.m_value*v.m_value}; } \
    template<int N> constexpr ClassName##T<N> One(ClassName##T<N>&) { return ClassName##T<N>::unit(); } \
    template<int N> constexpr ClassName##T<N> One(ClassName##T<N>&&) { return ClassName##T<N>::unit(); } \
    template<int N> constexpr ClassName##T<N> Zero(ClassName##T<N>&) { return ClassName##T<N>::zero(); } \
    template<int N> constexpr ClassName##T<N> Zero(ClassName##T<N>&&) { return ClassName##T<N>::zero(); } \

#define DECL_FWD(ClassName) \
template<int P> class ClassName##T; \

#endif // _FROGS_TYPES_CREATOR_H
