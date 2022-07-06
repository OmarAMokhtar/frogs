#ifndef _FROGS_EXPRESSIONS_H
#define _FROGS_EXPRESSIONS_H

#include <string>

namespace frogs
{

using Integer = unsigned long long;
using Real = long double;
using str = std::string;

class DummyClass {};

template<class T> str cov2str(T&& v) { return v.toString(); }
inline str cov2str(double v) { return std::to_string(v); }
inline str cov2str(Real v) { return std::to_string(v); }
inline str cov2str(Integer v) { return std::to_string(v); }
inline str cov2str(int v) { return std::to_string(v); }

template<typename T, class Dummy = DummyClass>
class Const
{
protected:
    T m_val;

public:
    constexpr Const(T v) : m_val{v} {}
    constexpr T val() { return m_val; }
    str toString() { return cov2str(m_val); }
};

extern Integer ___numVars;

template<typename T>
class Var
{
protected:
    T m_val;
    str m_name;

public:
    Var(T v) : m_val{v}
    {
        m_name = "var";
        m_name += std::to_string(++___numVars);
    }

    Var(T v, str name) : m_val{v}, m_name{name} {}

    Var<T>& operator=(T v)      { m_val =  v; return *this; }
    Var<T>& operator+=(T v)     { m_val += v; return *this; }
    Var<T>& operator-=(T v)     { m_val -= v; return *this; }
    Var<T>& operator*=(Real v)  { m_val *= v; return *this; }
    Var<T>& operator/=(Real v)  { m_val /= v; return *this; }

    constexpr T val() { return m_val; }
    str toString()
    {
        return m_name;
    }
};

/* Each operator class needs to handle a combination of values and pointers.
 * And these combinations apply for each operator. Some operators operate on
 * just one argument and others operate on two. So here we'll make macros
 * that declares these different classes for us.
 */

#define DECL_OPR_CLASS_1(ClassName, Func, Str1, Str2) \
template<class Exp, class Dummy = DummyClass> \
class ClassName##P { \
protected: \
    Exp* m_a; \
public: \
    constexpr ClassName##P(Exp* a) : m_a{a} {} \
    constexpr auto val() { return Func(m_a->val()); } \
    template<typename T = ClassName##P> \
    str toString() { \
        str s{Str1}; \
        s += m_a->toString(); \
        s += Str2; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, ClassName##P& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp* arg() { return m_a; } \
}; \
template<class Exp, class Dummy = DummyClass> \
class ClassName##V { \
protected: \
    Exp m_a; \
public: \
    constexpr ClassName##V(Exp a) : m_a{a} {} \
    constexpr auto val() { return Func(m_a.val()); } \
    str toString() { \
        str s{Str1}; \
        s += m_a.toString(); \
        s += Str2; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, ClassName##V& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp arg() { return m_a; } \
}; \

#define DECL_OPR_CLASS_2(ClassName, Func, Str1, Str2, Str3) \
template<class Exp0, class Exp1> \
class ClassName##VP { \
protected: \
    Exp0 m_a; \
    Exp1* m_b; \
public: \
    constexpr ClassName##VP(Exp0 a, Exp1* b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a.val(), m_b->val()); } \
    str toString() { \
        str s{Str1}; \
        s += m_a.toString(); \
        s += Str2; \
        s += m_b->toString(); \
        s += Str3; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, ClassName##VP& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp0 first() { return m_a; } \
    constexpr Exp1* second() { return m_b; } \
}; \
template<class Exp0, class Exp1> \
class ClassName##PV { \
protected: \
    Exp0* m_a; \
    Exp1 m_b; \
public: \
    constexpr ClassName##PV(Exp0* a, Exp1 b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a->val(), m_b.val()); } \
    str toString() { \
        str s{Str1}; \
        s += m_a->toString(); \
        s += Str2; \
        s += m_b.toString(); \
        s += Str3; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, ClassName##PV& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp0* first() { return m_a; } \
    constexpr Exp1 second() { return m_b; } \
}; \
template<class Exp0, class Exp1> \
class ClassName##VV { \
protected: \
    Exp0 m_a; \
    Exp1 m_b; \
public: \
    constexpr ClassName##VV(Exp0 a, Exp1 b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a.val(), m_b.val()); } \
    str toString() { \
        str s{Str1}; \
        s += m_a.toString(); \
        s += Str2; \
        s += m_b.toString(); \
        s += Str3; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, ClassName##VV& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp0 first() { return m_a; } \
    constexpr Exp1 second() { return m_b; } \
}; \
template<class Exp0, class Exp1> \
class ClassName##PP { \
protected: \
    Exp0* m_a; \
    Exp1* m_b; \
public: \
    constexpr ClassName##PP(Exp0* a, Exp1* b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func(m_a->val(), m_b->val()); } \
    str toString() { \
        str s{Str1}; \
        s += m_a->toString(); \
        s += Str2; \
        s += m_b->toString(); \
        s += Str3; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, ClassName##PP& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp0* first() { return m_a; } \
    constexpr Exp1* second() { return m_b; } \
}; \

#define DECL_OPR_2(Name, Opr) \
template<typename T0, typename T1> constexpr auto Name##Func(T0 a, T1 b) { return a Opr b; } \
DECL_OPR_CLASS_2(Name, Name##Func, "(", " " #Opr " ", ")") \
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
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name##VV<Exp0<A,B>,Const<T,DummyClass>> operator Opr(Exp0<A,B> a, T b) \
{ return {a, Const{b}}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name##VV<Const<T,DummyClass>,Exp0<A,B>> operator Opr(T a, Exp0<A,B> b) \
{ return {Const{a}, b}; } \
template<typename T0, typename T1> \
constexpr Name##VP<Const<T0,DummyClass>,Var<T1>> operator Opr(T0 a, Var<T1>& b) \
{ return {Const{a}, &b}; } \
template<typename T0, typename T1> \
constexpr Name##PV<Var<T0>,Const<T1,DummyClass>> operator Opr(Var<T0>& a, T1 b) \
{ return {&a, Const{b}}; } \

#define DECL_FUNC_2(Name, Func) \
DECL_OPR_CLASS_2(Name, Func, #Func "( ", ", ", " )") \
template<typename T0, typename T1> \
constexpr Name##PP<Var<T0>, Var<T1>> Func(Var<T0>& a, Var<T1>& b) \
{ return {&a, &b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name##PV<Var<T>,Exp<A,B>> Func(Var<T>& a, Exp<A,B> b) \
{ return {&a, b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name##VP<Exp<A,B>,Var<T>> Func(Exp<A,B> a, Var<T>& b) \
{ return {a, &b}; } \
template<typename A, typename B, \
         typename C, typename D, \
         template<class...> class Exp0, \
         template<class...> class Exp1> \
constexpr Name##VV<Exp0<A,B>,Exp1<C,D>> Func(Exp0<A,B> a, Exp1<C,D> b) \
{ return {a, b}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name##VV<Exp0<A,B>,Const<T,DummyClass>> Func(Exp0<A,B> a, T b) \
{ return {a, Const{b}}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name##VV<Const<T,DummyClass>,Exp0<A,B>> Func(T a, Exp0<A,B> b) \
{ return {Const{a}, b}; } \
template<typename T0, typename T1> \
constexpr Name##VP<Const<T0,DummyClass>,Var<T1>> Func(T0 a, Var<T1>& b) \
{ return {Const{a}, &b}; } \
template<typename T0, typename T1> \
constexpr Name##PV<Var<T0>,Const<T1,DummyClass>> Func(Var<T0>& a, T1 b) \
{ return {&a, Const{b}}; } \

#define DECL_OPR_1(Name, Opr) \
template<typename T> constexpr auto Name##Func(T a) { return Opr a; } \
DECL_OPR_CLASS_1(Name, Name##Func, "( " #Opr, " )") \
template<typename T> \
constexpr Name##P<Var<T>,DummyClass> operator Opr(Var<T>& a) \
{ return {&a}; } \
template<typename A, typename B, \
         template<class...> class Exp> \
constexpr Name##V<Exp<A,B>,DummyClass> operator Opr(Exp<A,B> a) \
{ return {a}; } \

#define DECL_FUNC_1(Name, Func) \
DECL_OPR_CLASS_1(Name, Func, #Func "( ", " )") \
template<typename T> \
constexpr Name##P<Var<T>,DummyClass> Func(Var<T>& a) \
{ return {&a}; } \
template<typename A, typename B, \
         template<class...> class Exp> \
constexpr Name##V<Exp<A,B>,DummyClass> Func(Exp<A,B> a) \
{ return {a}; } \

DECL_OPR_2(Add,+)
DECL_OPR_2(Sub,-)
DECL_OPR_2(Mul,*)
DECL_OPR_2(Div,/)
DECL_OPR_1(Neg,-)
DECL_OPR_1(Pos,+)
DECL_FUNC_1(AbsExp, Abs)
DECL_FUNC_1(CosExp, Cos)
DECL_FUNC_1(SinExp, Sin)
DECL_FUNC_1(TanExp, Tan)
DECL_FUNC_1(ACosExp, ACos)
DECL_FUNC_1(ASinExp, ASin)
DECL_FUNC_1(ATanExp, ATan)
DECL_FUNC_2(ATan2Exp, ATan2)

template<class T> constexpr auto $(T& v) { return v.val(); }

} // namespace frogs

#endif // _FROGS_EXPRESSIONS_H
