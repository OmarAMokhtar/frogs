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
