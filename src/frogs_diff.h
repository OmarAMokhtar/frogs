#ifndef _FROGS_DIFF_H
#define _FROGS_DIFF_H

#include <utility>
#include "frogs_expressions.h"

namespace frogs
{

template<typename T> constexpr T One(T&&) { return T::unit(); }
template<typename T> constexpr T Zero(T&&) { return T::zero(); }
constexpr Real One(Real) { return 1.0; }
constexpr Real Zero(Real) { return 0.0; }
constexpr Integer One(Integer) { return 1; }
constexpr Integer Zero(Integer) { return 0; }

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

template<typename A1, typename T>
constexpr auto Diff(AddPP<Var<T>,Var<T>> expr)
{
    return Const{2 * One(T{})};
}

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

template<typename A0, typename A1>
constexpr auto Diff(MulVV<A0,A1> expr)
{
    return Diff(expr.first()) * expr.second() + expr.first() + Diff(expr.second());
}

template<typename A0, typename T>
constexpr auto Diff(MulVP<A0,Var<T>> expr)
{
    return Diff(expr.first()) * expr.second() + expr.first() + Diff(expr.second());
}

template<typename A1, typename T>
constexpr auto Diff(MulPV<Var<T>,A1> expr)
{
    return Diff(expr.first()) * expr.second() + expr.first() + Diff(expr.second());
}

template<typename A1, typename T>
constexpr auto Diff(MulPP<Var<T>,Var<T>> expr)
{
    return MullVP{Const{One(T{}) * 2}, expr.first()};
}

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

} // namespace frogs

#endif // _FROGS_DIFF_H
