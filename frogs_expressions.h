#ifndef _FROGS_EXPRESSIONS_H
#define _FROGS_EXPRESSIONS_H

namespace frogs
{

using Integer = unsigned long long;
using Real = long double;

template<typename T>
class Const
{
protected:
    const T m_val;

public:
    constexpr Const(T v) : m_val{v} {}
    constexpr T val() { return m_val; }
};

template<typename T>
class Var
{
protected:
    T m_val;

public:
    Var(T v) : m_val{v} {}

    Var<T>& operator=(T v)      { m_val =  v; return *this; }
    Var<T>& operator+=(T v)     { m_val += v; return *this; }
    Var<T>& operator-=(T v)     { m_val -= v; return *this; }
    Var<T>& operator*=(Real v)  { m_val *= v; return *this; }
    Var<T>& operator/=(Real v)  { m_val /= v; return *this; }

    constexpr T val() { return m_val; }
};

/* Each operator class needs to handle a combination of values and pointers.
 * And these combinations apply for each operator. Some operators operate on
 * just one argument and others operate on two. So here we'll make macros
 * that declares these different classes for us.
 */

#define DECL_OPR_CLASS_1(ClassName, Func) \
template<class Exp> \
class ClassName##P { \
protected: \
    Exp* m_a; \
public: \
    constexpr ClassName##P(Exp* a) : m_a{a} {} \
    constexpr auto val() { return Func(m_a->val()); } \
}; \
template<class Exp> \
class ClassName##V { \
protected: \
    Exp m_a; \
public: \
    constexpr ClassName##P(Exp a) : m_a{a} {} \
    constexpr auto val() { return Func(m_a.val()); } \
}; \

#define DECL_OPR_CLASS_2(ClassName, Func) \
template<class Exp0, class Exp1> \
class ClassName##VP { \
protected: \
    Exp0 m_a; \
    Exp1* m_b; \
public: \
    constexpr ClassName##VP(Exp0 a, Exp1* b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a.val(), m_b->val()); } \
}; \
template<class Exp0, class Exp1> \
class ClassName##PV { \
protected: \
    Exp0* m_a; \
    Exp1 m_b; \
public: \
    constexpr ClassName##PV(Exp0* a, Exp1 b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a->val(), m_b.val()); } \
}; \
template<class Exp0, class Exp1> \
class ClassName##VV { \
protected: \
    Exp0 m_a; \
    Exp1 m_b; \
public: \
    constexpr ClassName##VV(Exp0 a, Exp1 b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a.val(), m_b.val()); } \
}; \
template<class Exp0, class Exp1> \
class ClassName##PP { \
protected: \
    Exp0* m_a; \
    Exp1* m_b; \
public: \
    constexpr ClassName##PP(Exp0* a, Exp1* b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a->val(), m_b->val()); } \
}; \

#define DECL_OPR_2(Name, Opr) \
template<typename T0, typename T1> constexpr auto Name##Func(T0 a, T1 b) { return a Opr b; } \
DECL_OPR_CLASS_2(Name, Name##Func) \
template<typename T0, typename T1> \
constexpr Name##PP<Var<T0>, Var<T1>> operator Opr(Var<T0>& a, Var<T1>& b) \
{ return {&a, &b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name##PV<Var<T>,Exp<A,B>> operator Opr(Var<T>& a, Exp<A,B> b) \
{ return {&a, b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name##VP<Exp<A,B>,Var<T>> operator Opr(Exp<A,B> a, Var<T>& b) \
{ return {a, &b}; } \
template<typename A, typename B, \
         typename C, typename D, \
         template<class...> class Exp0, \
         template<class...> class Exp1> \
constexpr Name##VV<Exp0<A,B>,Exp1<C,D>> operator Opr(Exp0<A,B> a, Exp1<C,D> b) \
{ return {a, b}; } \

DECL_OPR_2(Add,+)
DECL_OPR_2(Sub,-)
DECL_OPR_2(Mul,*)
DECL_OPR_2(Div,/)

template<class T> constexpr auto $(T& v) { return v.val(); }

} // namespace frogs

#endif // _FROGS_EXPRESSIONS_H
