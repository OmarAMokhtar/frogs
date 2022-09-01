#ifndef _FROGS_TYPES_FALLBACK_H
#define _FROGS_TYPES_FALLBACK_H

#include "frogs_primitives.h"

namespace frogs
{

/* These classes are place holders for units that we didn't define
 * a multiplication or division for. They'll just be glued together
 * until they're multiplied or divided by another unit and gets
 * converted to something else.
 * 
 * For example, we don't have a Distance * Time class. But if they
 * got multiplied, this class will hold that multiplication together
 * until it gets divided by Time for example. And then
 * the final result would be Distance again.
 */

/* This class is for multiplication. The DummyInt is added so that
 * it has 3 template arguments and not 2. This is to avoid confusion
 * with the expressions classes.
 */
template<class A, class B, int DummyInt = 0>
class UnitsMul
{
public:
    A m_a;
    B m_b;
    constexpr UnitsMul(A a, B b) : m_a{a}, m_b{b} {}
};

/* And this one is for division */
template<class A, class B, int DummyInt = 0>
class UnitsDiv
{
public:
    A m_a;
    B m_b;
    constexpr UnitsDiv(A a, B b) : m_a{a}, m_b{b} {}
};

/* These are the main operators that create objects of these
 * classes. If there are already explicit operators for the
 * types being multiplied or divided, the compiler will chose
 * that overload instead. Otherwise if it's not defined, the
 * choice will fall back to these.
 */
template<int PA, template<int...> class A, int PB, template<int...> class B>
constexpr auto operator*(Unit<PA,A> a, Unit<PB,B> b)
{ return UnitsMul{a,b}; }

template<int PA, template<int...> class A, int PB, template<int...> class B>
constexpr auto operator/(Unit<PA,A> a, Unit<PB,B> b)
{ return UnitsDiv{a,b}; }

/* These are some of the relations that breaks these classes
 * and results in one of the defined physical types.
 */
template<typename A, typename B>
constexpr auto operator/(UnitsMul<A,B,0> a, B b) { return a.m_a * (a.m_b / b); }
template<typename A, typename B>
constexpr auto operator/(UnitsMul<B,A,0> a, B b) { return a.m_b * (a.m_a / b); }
template<typename A, typename B>
constexpr auto operator*(UnitsDiv<A,B,0> a, B b) { return a.m_a * (b / a.m_b); }
template<typename A, typename B>
constexpr auto operator*(A a, UnitsDiv<B,A,0> b) { return b.m_a * (a / b.m_b); }
template<typename A, typename B>
constexpr auto operator*(UnitsMul<A,B,0> a, UnitsDiv<A,B,0> b) { return (b.m_a * a.m_a) * (a.m_b / b.m_b); }
template<typename A, typename B, typename C>
constexpr auto operator*(UnitsMul<A,B,0> a, UnitsDiv<C,B,0> b) { return (a.m_b / b.m_b) * (a.m_a * b.m_a); }
template<typename A, typename B, typename C>
constexpr auto operator*(UnitsDiv<C,B,0> b, UnitsMul<A,B,0> a) { return (a.m_b / b.m_b) * (a.m_a * b.m_a); }
template<typename A, typename B, typename C>
constexpr auto operator*(UnitsMul<B,A,0> a, UnitsDiv<C,B,0> b) { return (a.m_a / b.m_b) * (a.m_b * b.m_a); }
template<typename A, typename B, typename C>
constexpr auto operator*(UnitsDiv<C,B,0> b, UnitsMul<B,A,0> a) { return (a.m_a / b.m_b) * (a.m_b * b.m_a); }
template<typename A, typename B, typename C>
constexpr auto operator/(UnitsMul<A,B,0> a, UnitsMul<B,C,0> b) { return (a.m_b / b.m_a) * (a.m_a / b.m_b); }
template<typename A, typename B>
constexpr auto operator/(UnitsMul<A,B,0> a, UnitsMul<B,B,0> b) { return (a.m_b / b.m_a) * (a.m_a / b.m_b); }
template<typename A, typename B, typename C>
constexpr auto operator/(UnitsMul<A,B,0> a, UnitsMul<C,B,0> b) { return (a.m_b / b.m_b) * (a.m_a / b.m_a); }

template<typename A, int N, int M, template<int...> class B>
constexpr auto operator/(UnitsMul<A,Unit<N,B>,0> a, Unit<M,B> b)
{ return a.m_a * (a.m_b / b); }

template<typename A, int N, int M, template<int...> class B>
constexpr auto operator/(UnitsMul<Unit<N,B>,A,0> a, Unit<M,B> b)
{ return a.m_b * (a.m_a / b); }

} // namespace frogs

#endif // _FROGS_TYPES_FALLBACK_H
