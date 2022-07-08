#ifndef _FROGS___Diff_H
#define _FROGS___Diff_H

#include <utility>
#include "frogs_expressions.h"

namespace frogs
{

/* These functions help get a zero or a one value from a certain type.
 * That type could be one of the physical types or a C++ primitive.
 * Either way, one of these functions will match and return a one or
 * a zero. We need them for __Differentiating a variable and it resolves
 * to one or a constant and it resolves to zero.
 */

template<typename T> constexpr T One(T&&) { return T::unit(); }
template<typename T> constexpr T Zero(T&&) { return T::zero(); }
constexpr Real One(Real) { return 1.0; }
constexpr Real Zero(Real) { return 0.0; }
constexpr double One(double) { return 1.0; }
constexpr double Zero(double) { return 0.0; }
constexpr Integer One(Integer) { return 1; }
constexpr Integer Zero(Integer) { return 0; }
constexpr int One(int) { return 1; }
constexpr int Zero(int) { return 0; }

/* The simplest __Differentiation rules. Variables become one and
 * constants become zero.
 */

template<typename T>
constexpr auto __Diff(Var<T> expr)
{
    return Const{One(T{})};
}

template<typename T>
constexpr auto __Diff(Var<T>* expr)
{
    return Const{One(T{})};
}

template<typename T>
constexpr Var<T>& Same(Var<T>* expr)
{
    return *expr;
}

template<typename Exp>
constexpr auto Same(Exp&& expr)
{
    return expr;
}

template<typename T>
constexpr auto __Diff(Const<T> expr)
{
    return ZeroExp<T>{};
}

template<typename Exp>
constexpr auto __Diff(Neg<Exp,DummyClass> expr)
{
    return Neg{__Diff(expr.arg())};
}

template<typename Exp>
constexpr auto __Diff(Pos<Exp,DummyClass> expr)
{
    return __Diff(expr.arg());
}

/* Addition rules in __Differentiation.
 *
 * if f(x) = g(x) + h(x)
 * then f`(x) = g`(x) + h`(x)
 */

template<typename A0, typename A1>
constexpr auto __Diff(Add<A0,A1> expr)
{
    return (__Diff(expr.first()) + __Diff(expr.second()));
}

/* Subtraction rules in __Differentiation.
 *
 * if f(x) = g(x) - h(x)
 * then f`(x) = g`(x) - h`(x)
 */

template<typename A0, typename A1>
constexpr auto __Diff(Sub<A0,A1> expr)
{
    return (__Diff(expr.first()) - __Diff(expr.second()));
}

/* Multiplication rules in __Differentiation.
 *
 * if f(x) = g(x) * h(x)
 * then f`(x) = g`(x) * h(x) + g(x) * h`(x)
 */

template<typename A0, typename A1>
constexpr auto __Diff(Mul<A0,A1> expr)
{
    return ((__Diff(expr.first()) * Same(expr.second()))
            + (Same(expr.first()) * __Diff(expr.second())));
}

/* Division rules in __Differentiation.
 *
 * if f(x) = g(x) / h(x)
 * then f`(x) = ( g`(x) * h(x) - g(x) * h`(x) ) / ( h(x) * h(x) )
 */
template<typename A0, typename A1>
constexpr auto __Diff(Div<A0,A1> expr)
{
    return (((__Diff(expr.first()) * Same(expr.second()))
                - (Same(expr.first()) * __Diff(expr.second())))
            / (Same(expr.second()) * Same(expr.second())));
}

/* Trignometry rules in __Differentiation.
 *
 * if f(x) = Cos(g(x))
 * then f`(x) = Sin(g(x)) * g`(x)
 * 
 * if f(x) = Sin(g(x))
 * then f`(x) = -Cos(g(x)) * g`(x)
 * 
 * if f(x) = Tan(g(x))
 * then f`(x) = g`(x) / (Cos(g(x)) * Cos(g(x)))
 * 
 * if f(x) = ASin(g(x))
 * then f`(x) = g`(x) / Sqrt(1 - g(x) * g(x))
 * 
 * if f(x) = ACos(g(x))
 * then f`(x) = g`(x) / Sqrt(g(x) * g(x) - 1)
 * 
 * if f(x) = ATan(g(x))
 * then f`(x) = g`(x) / 1 - (g(x) * g(x))
 */

template<typename Exp>
constexpr auto __Diff(CosExp<Exp,DummyClass> expr)
{
    return (Sin(Same(expr.arg())) * __Diff(expr.arg()));
}

template<typename Exp>
constexpr auto __Diff(SinExp<Exp,DummyClass> expr)
{
    return (-Cos(Same(expr.arg())) * __Diff(expr.arg()));
}

template<typename Exp>
constexpr auto __Diff(TanExp<Exp,DummyClass> expr)
{
    return (__Diff(expr.arg()) / (Cos(Same(expr.arg())) * Cos(Same(expr.arg()))));
}

template<typename Exp, typename DT>
constexpr auto Diff(Exp expr, Var<DT>& dt)
{
    return __Diff(expr) / Const{One(DT{})};
}

} // namespace frogs

#endif // _FROGS___Diff_H
