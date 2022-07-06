#ifndef _FROGS_DIFF_H
#define _FROGS_DIFF_H

#include <utility>
#include "frogs_expressions.h"

namespace frogs
{

/* These functions help get a zero or a one value from a certain type.
 * That type could be one of the physical types or a C++ primitive.
 * Either way, one of these functions will match and return a one or
 * a zero. We need them for differentiating a variable and it resolves
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

/* The simplest differentiation rules. Variables become one and
 * constants become zero.
 */

template<typename T>
constexpr auto Diff(Var<T> expr)
{
    return Const{One(T{})};
}

template<typename T>
constexpr auto Diff(Const<T> expr)
{
    return Const{Zero(T{})};
}

template<typename T>
constexpr auto Diff(NegP<Var<T>> expr)
{
    return Const{One(T{}) * -1};
}

template<typename Exp>
constexpr auto Diff(NegV<Exp> expr)
{
    return -Diff(expr.arg());
}

template<typename T>
constexpr auto Diff(PosP<Var<T>> expr)
{
    return Const{One(T{})};
}

template<typename Exp>
constexpr auto Diff(PosV<Exp> expr)
{
    return Diff(expr.arg());
}

/* Addition rules in differentiation.
 *
 * if f(x) = g(x) + h(x)
 * then f`(x) = g`(x) + h`(x)
 */

template<typename A0, typename A1>
constexpr auto Diff(AddVV<A0,A1> expr)
{
    return Diff(expr.first()) + Diff(expr.second());
}

template<typename A0, typename T>
constexpr auto Diff(AddVP<A0,Var<T>> expr)
{
    return Diff(expr.first()) + Const{One(T{})};
}

template<typename A1, typename T>
constexpr auto Diff(AddPV<Var<T>,A1> expr)
{
    return Const{One(T{})} + Diff(expr.second());
}

template<typename T>
constexpr auto Diff(AddPP<Var<T>,Var<T>> expr)
{
    return Const{2 * One(T{})};
}

/* Subtraction rules in differentiation.
 *
 * if f(x) = g(x) - h(x)
 * then f`(x) = g`(x) - h`(x)
 */

template<typename A0, typename A1>
constexpr auto Diff(SubVV<A0,A1> expr)
{
    return Diff(expr.first()) - Diff(expr.second());
}

template<typename A0, typename T>
constexpr auto Diff(SubVP<A0,Var<T>> expr)
{
    return Diff(expr.first()) - Const{One(T{})};
}

template<typename A1, typename T>
constexpr auto Diff(SubPV<Var<T>,A1> expr)
{
    return Const{One(T{})} - Diff(expr.second());
}

template<typename A1, typename T>
constexpr auto Diff(SubPP<Var<T>,Var<T>> expr)
{
    return Const{Zero(T{})};
}

/* Multiplication rules in differentiation.
 *
 * if f(x) = g(x) * h(x)
 * then f`(x) = g`(x) * h(x) + g(x) * h`(x)
 */

template<typename A0, typename A1>
constexpr auto Diff(MulVV<A0,A1> expr)
{
    return Diff(expr.first()) * expr.second() + expr.first() + Diff(expr.second());
}

template<typename A0, typename T>
constexpr auto Diff(MulVP<A0,Var<T>> expr)
{
    return MulVP{Diff(expr.first()), expr.second()} + expr.first();
}

template<typename A1, typename T>
constexpr auto Diff(MulPV<Var<T>,A1> expr)
{
    return MulPV{expr.first(), Diff(expr.second())} + expr.second();
}

template<typename T>
constexpr auto Diff(MulPP<Var<T>,Var<T>> expr)
{
    return MulVP{Const{One(T{}) * 2}, expr.first()};
}

/* Division rules in differentiation.
 *
 * if f(x) = g(x) / h(x)
 * then f`(x) = ( g`(x) * h(x) - g(x) * h`(x) ) / ( h(x) * h(x) )
 */
template<typename A0, typename A1>
constexpr auto Diff(DivVV<A0,A1> expr)
{
    return ((Diff(expr.first()) * expr.second())
                - (expr.first() * Diff(expr.second())))
            / (expr.second() * expr.second());
}

template<typename A0, typename T>
constexpr auto Diff(DivVP<A0,Var<T>> expr)
{
    return ((Diff(expr.first()) * expr.second()) - expr.first())
            / (expr.second() * expr.second());
}

template<typename A1, typename T>
constexpr auto Diff(DivPV<Var<T>,A1> expr)
{
    return (expr.second() - (expr.first() * Diff(expr.second())))
            / (expr.second() * expr.second());
}

template<typename T>
constexpr auto Diff(DivPP<Var<T>,Var<T>> expr)
{
    return Const{Zero(T{})};
}

} // namespace frogs

#endif // _FROGS_DIFF_H
