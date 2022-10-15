#ifndef _FROGS_TYPES_CREATOR_H
#define _FROGS_TYPES_CREATOR_H

#include <cstdint>
#include <iostream>
#include <string>
#include <limits>
#include <type_traits>

#ifdef QT_VERSION
# include <QDebug>
#endif

#include "frogs_primitives.h"
#include "frogs_vector.h"

namespace frogs
{
template<int P, template<int...> class T>
class Unit
{
private:
    T<P> m_value;

public:
    using Self = Unit<P,T>;
    constexpr Unit() : m_value{} {}
    constexpr Unit(T<P> v) : m_value{v} {}
    static constexpr Self zero() { return {T<P>::zero()}; }
    static constexpr Self unit() { return {T<P>::unit()}; }
    static constexpr Self max() { return {T<P>::max()}; }
    static constexpr Self min() { return {T<P>::min()}; }
    constexpr Self& operator+=(Self a) { m_value += $(a); return *this; }
    constexpr Self& operator-=(Self a) { m_value -= $(a); return *this; }
    constexpr Self& operator*=(Real a) { m_value *= a; return *this; }
    constexpr Self& operator/=(Real a) { m_value *= a; return *this; }
    constexpr Self& operator=(Self a) { m_value = $(a); return *this; }
    constexpr auto operator,(Self other) { return Vec2{*this, other}; }
    constexpr auto operator,(Vec2<Self> other) { return Vec3{*this, other}; }
    constexpr auto operator,(Vec3<Self> other) { return Vec4{*this, other}; }

    Str toString() const { return m_value.toString(); }

#ifdef QT_VERSION
    friend QDebug operator<<(QDebug d, Self v) {
        d << v.toString().data();
        return d;
    }
#endif

    template<int N, template<int...> class C>
    friend constexpr C<N> $(Unit<N,C> a);
};

template<int N, template<int...> class C>
constexpr C<N> $(Unit<N,C> a)
{ return a.m_value; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator-(Unit<P,T> a)
{ return {-$(a)}; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator+(Unit<P,T> a)
{ return a; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator+(Unit<P,T> a, Unit<P,T> b)
{ return {$(a) + $(b)}; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator-(Unit<P,T> a, Unit<P,T> b)
{ return {$(a) - $(b)}; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator*(Real a, Unit<P,T> b)
{ return {a * $(b)}; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator*(Unit<P,T> a, Real b)
{ return {$(a) * b}; }

template<int P, template<int...> class T>
constexpr Unit<P,T> operator/(Unit<P,T> a, Real b)
{ return {$(a) / b}; }

template<int P, template<int...> class T>
constexpr Unit<-P,T> operator/(Real a, Unit<P,T> b)
{ return {a / $(b)}; }

template<int N, int M, template<int...> class T>
constexpr Unit<N+M,T> operator*(Unit<N,T> a, Unit<M,T> b)
{ return {$(a) * $(b)}; }

template<int N, int M, template<int...> class T>
constexpr Unit<N-M,T> operator/(Unit<N,T> a, Unit<M,T> b)
{ return {$(a) / $(b)}; }

template<int N, template<int...> class T>
constexpr Real operator/(Unit<N,T> a, Unit<N,T> b)
{ return $(a) / $(b); }

template<int N, template<int...> class T>
constexpr bool operator==(Unit<N,T> a, Unit<N,T> b)
{ return $(a) == $(b); }

template<int N, template<int...> class T>
constexpr bool operator!=(Unit<N,T> a, Unit<N,T> b)
{ return $(a) != $(b); }

template<int N, template<int...> class T>
constexpr bool operator>(Unit<N,T> a, Unit<N,T> b)
{ return $(a) > $(b); }

template<int N, template<int...> class T>
constexpr bool operator>=(Unit<N,T> a, Unit<N,T> b)
{ return $(a) >= $(b); }

template<int N, template<int...> class T>
constexpr bool operator<(Unit<N,T> a, Unit<N,T> b)
{ return $(a) < $(b); }

template<int N, template<int...> class T>
constexpr bool operator<=(Unit<N,T> a, Unit<N,T> b)
{ return $(a) <= $(b); }

template<int N, template<int...> class T>
constexpr Unit<N,T> Abs(Unit<N,T> v)
{ return {Abs($(v))}; }

template<template<int...> class T>
constexpr Unit<1,T> Sqrt(Unit<2,T> v)
{ return {Sqrt($(v))}; }

template<template<int...> class T>
constexpr Unit<2,T> Sqrt(Unit<4,T> v)
{ return {Sqrt($(v))}; }

template<template<int...> class T>
constexpr Unit<3,T> Sqrt(Unit<6,T> v)
{ return {Sqrt($(v))}; }

template<template<int...> class T>
constexpr Unit<4,T> Sqrt(Unit<8,T> v)
{ return {Sqrt($(v))}; }

template<int N, template<int...> class T>
constexpr Unit<N*2,T> Sqr(Unit<N,T> v)
{ return {Sqr($(v))}; }

template<int N, template<int...> class T>
constexpr Unit<N*3,T> Cube(Unit<N,T> v)
{ return {Cube($(v))}; }

template<int N, template<int...> class T>
constexpr Unit<N,T> One(Unit<N,T>& a)
{ return {One($(a))}; }

template<int N, template<int...> class T>
constexpr Unit<N,T> One(Unit<N,T>&& a)
{ return {One($(a))}; }

template<int N, template<int...> class T>
constexpr Unit<N,T> Zero(Unit<N,T>& a)
{ return {Zero($(a))}; }

template<int N, template<int...> class T>
constexpr Unit<N,T> Zero(Unit<N,T>&& a)
{ return {Zero($(a))}; }

template<int N, template<int...> class T>
std::ostream &operator<<(std::ostream &output, Unit<N,T> obj) {
    output << obj.toString();
    return output;
}

} // namespace frogs

/* The macros that helps build classes */

#define DECL_UNIT(Result, P, Sym, Getter, Scale) \
    static constexpr Real convFrom##Sym = Scale; \
    constexpr Real Getter() const { \
        assert(this->order() == P); \
        return m_value / (convFrom##Sym); }

#define IMPL_UNIT(ClassName, P, Symb) \
    constexpr Unit<P,ClassName> operator""##Symb(unsigned long long v) \
    { return {ClassName<P>{v * ClassName<P>::convFrom##Symb}}; } \
    constexpr Unit<P,ClassName> operator""##Symb(long double v) \
    { return {ClassName<P>{static_cast<Real>(v * ClassName<P>::convFrom##Symb)}}; }

#define DECL_CONV(Result, P, ClassA, PA, Opr, ClassB, PB) \
    friend constexpr Unit<P,Result> operator Opr(Unit<PA,ClassA> a, Unit<PB,ClassB> b);

#define IMPL_CONV(Result, P, ClassA, PA, UnitA, Opr, ClassB, PB, UnitB) \
    constexpr Unit<P,Result> operator Opr(Unit<PA,ClassA> a, Unit<PB,ClassB> b) \
    { return {$(a).UnitA() Opr $(b).UnitB()}; }

#define DECL_CONV_ADD(Result, P, ClassA, PA, ClassB, PB) \
    DECL_CONV(Result, P, ClassA, PA, +, ClassB, PB) \
    DECL_CONV(Result, P, ClassB, PB, +, ClassA, PA)

#define IMPL_CONV_ADD(Result, P, ClassA, PA, UnitA, ClassB, PB, UnitB) \
    IMPL_CONV(Result, P, ClassA, UnitA, PA, +, ClassB, UnitB, PB) \
    IMPL_CONV(Result, P, ClassB, UnitB, PB, +, ClassA, UnitA, PA)

#define DECL_CONV_SUB(Result, P, ClassA, PA, ClassB, PB) \
    DECL_CONV(Result, P, ClassA, PA, -, ClassB, PB) \
    DECL_CONV(Result, P, ClassB, PA, -, ClassA, PA)

#define IMPL_CONV_SUB(Result, P, ClassA, PA, UnitA, ClassB, PB, UnitB) \
    IMPL_CONV(Result, P, ClassA, PA, UnitA, -, ClassB, PB, UnitB) \
    IMPL_CONV(Result, P, ClassB, PB, UnitB, -, ClassA, PA, UnitA)

#define DECL_CONV_MUL(Result, P, ClassA, PA, ClassB, PB) \
    DECL_CONV(Result, P, ClassA, PA, *, ClassB, PB) \
    DECL_CONV(Result, P, ClassB, PB, *, ClassA, PA) \

#define IMPL_CONV_MUL(Result, P, ClassA, PA, UnitA, ClassB, PB, UnitB) \
    IMPL_CONV(Result, P, ClassA, PA, UnitA, *, ClassB, PB, UnitB) \
    IMPL_CONV(Result, P, ClassB, PB, UnitB, *, ClassA, PA, UnitA) \

#define DECL_CONV_SQR(Result, P, Class, PC) \
    DECL_CONV(Result, P, Class, PC, *, Class, PC) \

#define IMPL_CONV_SQR(Result, P, Class, PC, Unit) \
    IMPL_CONV(Result, P, Class, PC, Unit, *, Class, PC, Unit) \

#define DECL_CONV_DIV(Result, P, ClassA, PA, ClassB, PB) \
    DECL_CONV(Result, P, ClassA, PA, /, ClassB, PB)

#define IMPL_CONV_DIV(Result, P, ClassA, PA, UnitA, ClassB, PB, UnitB) \
    IMPL_CONV(Result, P, ClassA, PA, UnitA, /, ClassB, PB, UnitB)

#define DECL_CONV_AB_DIV_C(Result, P, ClassA, PA, ClassB, PB, ClassC, PC) \
    friend constexpr Unit<P,Result> operator/(UnitsMul<Unit<PA,ClassA>,Unit<PB,ClassB>,0>, Unit<PC,ClassC>); \
    friend constexpr Unit<P,Result> operator/(UnitsMul<Unit<PB,ClassB>,Unit<PA,ClassA>,0>, Unit<PC,ClassC>); \
    friend constexpr Unit<P,Result> operator*(Unit<PA,ClassA>, UnitsDiv<Unit<PB,ClassB>,Unit<PC,ClassC>,0>); \
    friend constexpr Unit<P,Result> operator*(Unit<PB,ClassB>, UnitsDiv<Unit<PA,ClassA>,Unit<PC,ClassC>,0>); \
    friend constexpr Unit<P,Result> operator*(UnitsDiv<Unit<PB,ClassB>,Unit<PC,ClassC>,0>, Unit<PA,ClassA>); \
    friend constexpr Unit<P,Result> operator*(UnitsDiv<Unit<PA,ClassA>,Unit<PC,ClassC>,0>, Unit<PB,ClassB>);

#define IMPL_CONV_AB_DIV_C(Result, P, ClassA, PA, UnitA, ClassB, PB, UnitB, ClassC, PC, UnitC) \
    constexpr Unit<P,Result> operator/(UnitsMul<Unit<PA,ClassA>,Unit<PB,ClassB>,0> ab, Unit<PC,ClassC> c) \
    { return {($(ab.m_a).UnitA() * $(ab.m_b).UnitB()) / $(c).UnitC()}; } \
    constexpr Unit<P,Result> operator/(UnitsMul<Unit<PB,ClassB>,Unit<PA,ClassA>,0> ab, Unit<PC,ClassC> c) \
    { return {($(ab.m_a).UnitB() * $(ab.m_b).UnitA()) / $(c).UnitC()}; } \
    constexpr Unit<P,Result> operator*(Unit<PA,ClassA> a, UnitsDiv<Unit<PB,ClassB>,Unit<PC,ClassC>,0> b_c) \
    { return {$(a).UnitA() * ($(b_c.m_a).UnitB() / $(b_c.m_b).UnitC())}; } \
    constexpr Unit<P,Result> operator*(Unit<PB,ClassB> b, UnitsDiv<Unit<PA,ClassA>,Unit<PC,ClassC>,0> a_c) \
    { return {$(b).UnitB() * ($(a_c.m_a).UnitA() / $(a_c.m_b).UnitC())}; } \
    constexpr Unit<P,Result> operator*(UnitsDiv<Unit<PB,ClassB>,Unit<PC,ClassC>,0> b_c, Unit<PA,ClassA> a) \
    { return {($(b_c.m_a).UnitB() / $(b_c.m_b).UnitC()) * $(a).UnitA()}; } \
    constexpr Unit<P,Result> operator*(UnitsDiv<Unit<PA,ClassA>,Unit<PC,ClassC>,0> a_c, Unit<PB,ClassB> b) \
    { return {($(a_c.m_a).UnitA() / $(a_c.m_b).UnitC()) * $(b).UnitB()}; }

#define DECL_CLASS(ClassName, String, PublicDecl) \
template<int P = 1> \
class ClassName##T { \
private: \
    Real m_value; \
public: \
    constexpr ClassName##T() : m_value(0.0) {} \
    constexpr ClassName##T(Real v) : m_value(v) {} \
    using Self = ClassName##T<P>; \
    static constexpr auto order() { return P; } \
    static constexpr Self zero() { return {0.0}; } \
    static constexpr Self unit() { return {1.0}; } \
    static constexpr Self max() { return {std::numeric_limits<Real>::max()}; } \
    static constexpr Self min() { return {std::numeric_limits<Real>::min()}; } \
    constexpr Self& operator+=(Self a) { m_value += a.m_value; return *this; } \
    constexpr Self& operator-=(Self a) { m_value -= a.m_value; return *this; } \
    constexpr Self& operator*=(Real a) { m_value *= a; return *this; } \
    constexpr Self& operator/=(Real a) { m_value *= a; return *this; } \
    constexpr Self& operator=(Self a) { m_value = a.m_value; return *this; } \
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
    template<int N> constexpr ClassName##T<N> Zero(ClassName##T<N>&&) { return ClassName##T<N>::zero(); }

#define DECL_FWD(ClassName) \
template<int P> class ClassName##T;

#endif // _FROGS_TYPES_CREATOR_H
