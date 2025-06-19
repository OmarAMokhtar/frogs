#ifndef _FROGS_Diff_H
#define _FROGS_Diff_H

#include <utility>
#include <cassert>
#include "frogs_expressions.h"

namespace frogs
{

/* These functions help get a zero or a one value from a certain type.
 * That type could be one of the physical types or a C++ primitive.
 * Either way, one of these functions will match and return a one or
 * a zero. We need them for Differentiating a variable and it resolves
 * to one or a constant and it resolves to zero.
 */

/* The simplest Differentiation rules. Variables become one and
 * constants become zero.
 */

template<typename T, typename DT>
constexpr auto __Diff(Var<T>& expr, Var<DT>& dt)
{
    /* Only one variable is supported in differentiation now */
    assert(&dt == &expr);
    return Const{One(T{})};
}

template<typename T, typename DT>
constexpr auto __Diff(Var<T>* expr, Var<DT>& dt)
{
    /* Only one variable is supported in differentiation now */
    assert(&dt == expr);
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

template<typename T, typename DT>
constexpr auto __Diff(Const<T> expr, Var<DT>& dt)
{
    return ZeroExp<T>{};
}

template<typename Exp, typename DT>
constexpr auto __Diff(Neg<Exp,DummyClass> expr, Var<DT>& dt)
{
    return Neg{__Diff(expr.arg(),dt)};
}

template<typename Exp, typename DT>
constexpr auto __Diff(Pos<Exp,DummyClass> expr, Var<DT>& dt)
{
    return __Diff(expr.arg(),dt);
}

/* Addition rules in Differentiation.
 *
 * if f(x) = g(x) + h(x)
 * then f`(x) = g`(x) + h`(x)
 */

template<typename A0, typename A1, typename DT>
constexpr auto __Diff(Add<A0,A1> expr, Var<DT>& dt)
{
    return (__Diff(expr.first(),dt) + __Diff(expr.second(),dt));
}

/* Subtraction rules in Differentiation.
 *
 * if f(x) = g(x) - h(x)
 * then f`(x) = g`(x) - h`(x)
 */

template<typename A0, typename A1, typename DT>
constexpr auto __Diff(Sub<A0,A1> expr, Var<DT>& dt)
{
    return (__Diff(expr.first(),dt) - __Diff(expr.second(),dt));
}

/* Multiplication rules in Differentiation.
 *
 * if f(x) = g(x) * h(x)
 * then f`(x) = g`(x) * h(x) + g(x) * h`(x)
 */

template<typename A0, typename A1, typename DT>
constexpr auto __Diff(Mul<A0,A1> expr, Var<DT>& dt)
{
    return ((__Diff(expr.first(),dt) * Same(expr.second()))
            + (Same(expr.first()) * __Diff(expr.second(),dt)));
}

/* Division rules in Differentiation.
 *
 * if f(x) = g(x) / h(x)
 * then f`(x) = ( g`(x) * h(x) - g(x) * h`(x) ) / ( h(x) * h(x) )
 */
template<typename A0, typename A1, typename DT>
constexpr auto __Diff(Div<A0,A1> expr, Var<DT>& dt)
{
    return (((__Diff(expr.first(),dt) * Same(expr.second()))
                - (Same(expr.first()) * __Diff(expr.second(),dt)))
            / (Same(expr.second()) * Same(expr.second())));
}

/* Trignometry rules in Differentiation.
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

template<typename Exp, typename DT>
constexpr auto __Diff(CosExp<Exp,DummyClass> expr, Var<DT>& dt)
{
    return (Sin(Same(expr.arg())) * __Diff(expr.arg(),dt));
}

template<typename Exp, typename DT>
constexpr auto __Diff(SinExp<Exp,DummyClass> expr, Var<DT>& dt)
{
    return (-Cos(Same(expr.arg())) * __Diff(expr.arg(),dt));
}

template<typename Exp, typename DT>
constexpr auto __Diff(TanExp<Exp,DummyClass> expr, Var<DT>& dt)
{
    return (__Diff(expr.arg(),dt) / (Cos(Same(expr.arg())) * Cos(Same(expr.arg()))));
}

/* 
 * Square root rules in differentiation
 * 
 * if f(x) = sqrt(g(x))
 * then f`(x) = g`(x) / ( 2 * sqrt(g(x)) )
 */

template<typename Exp, typename DT>
constexpr auto __Diff(SqrtExp<Exp,DummyClass> expr, Var<DT>& dt)
{
    return (__Diff(expr.arg(),dt) / (2 * expr));
}

/* 
 * Square and Cube rules in differentiation
 * 
 * if f(x) = g(x)^N
 * then f`(x) = g`(x) * N * g(x)^(N-1)
 */

template<typename Exp, typename DT>
constexpr auto __Diff(SqrExp<Exp,DummyClass> expr, Var<DT>& dt)
{
    return (__Diff(expr.arg(),dt) * 2 * Same(expr.arg()));
}

template<typename Exp, typename DT>
constexpr auto __Diff(CubeExp<Exp,DummyClass> expr, Var<DT>& dt)
{
    return (__Diff(expr.arg(),dt) * 3 * Sqr(Same(expr.arg())));
}

/* This is the main Differentiation function. The only difference
 * between this and the others is that it divides by a unit of the
 * differentiation variable.
 */
template<typename Exp, typename DT>
constexpr auto Diff(Exp expr, Var<DT>& dt)
{
    return __Diff(expr,dt) / Const{One(DT{})};
}

} // namespace frogs

#endif // _FROGS_Diff_H
