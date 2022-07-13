#ifndef _FROGS_EXPRESSIONS_H
#define _FROGS_EXPRESSIONS_H

#include <string>
#include <math.h>

#include "frogs_primitives.h"

namespace frogs
{

class DummyClass {};

class Expr
{
protected:
    virtual void read(void* v) = 0;

public:
    template<typename T = Real> T val() { T v; read(&v); return v; }
    virtual Str toString() const = 0;
};

template<typename T, class Dummy = DummyClass>
class Const : public Expr
{
protected:
    T m_val;

    virtual void read(void* v) { *reinterpret_cast<T*>(v) = val(); }

public:
    constexpr Const(T v) : m_val{v} {}
    constexpr T val() { return m_val; }
    virtual Str toString() const { return conv2str(m_val); }
};

template<typename T, class Dummy = DummyClass>
class ZeroExp : public Expr
{
protected:
    virtual void read(void* v) { *reinterpret_cast<T*>(v) = val(); }

public:
    constexpr ZeroExp() {}
    constexpr ZeroExp(T v) {}
    constexpr T val() { return ZeroExp(T{}); }
    virtual Str toString() const { return "0"; }
};

extern Integer ___numVars;

template<typename T>
class Var : public Expr
{
protected:
    T m_val;
    Str m_name;

    virtual void read(void* v) { *reinterpret_cast<T*>(v) = val(); }

public:
    Var(T v) : m_val{v}
    {
        m_name = "var";
        m_name += std::to_string(++___numVars);
    }

    Var(T v, Str name) : m_val{v}, m_name{name} {}

    Var<T>& operator=(T v)      { m_val =  v; return *this; }
    Var<T>& operator+=(T v)     { m_val += v; return *this; }
    Var<T>& operator-=(T v)     { m_val -= v; return *this; }
    Var<T>& operator*=(Real v)  { m_val *= v; return *this; }
    Var<T>& operator/=(Real v)  { m_val /= v; return *this; }

    bool operator<(T v)  { return m_val < v; }
    bool operator>(T v)  { return m_val > v; }
    bool operator<=(T v) { return m_val <= v; }
    bool operator>=(T v) { return m_val >= v; }
    bool operator==(T v) { return m_val == v; }
    bool operator!=(T v) { return m_val != v; }

    constexpr T val() { return m_val; }

    virtual Str toString() const
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
template<typename Exp, class Dummy = DummyClass> \
class ClassName : public Expr { \
protected: \
    Exp m_a; \
    virtual void read(void* v) { *reinterpret_cast<decltype(val())*>(v) = val(); } \
public: \
    constexpr ClassName(Exp a) : m_a{a} {} \
    constexpr auto val() { return Func($(m_a)); } \
    virtual Str toString() const { \
        Str s{Str1}; \
        s += conv2str(m_a); \
        s += Str2; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, const ClassName& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp* arg() { return m_a; } \
}; \

#define DECL_OPR_CLASS_2(ClassName, Func, Str1, Str2, Str3) \
template<class Exp0, class Exp1> \
class ClassName : public Expr { \
protected: \
    Exp0 m_a; \
    Exp1 m_b; \
    virtual void read(void* v) { *reinterpret_cast<decltype(val())*>(v) = val(); } \
public: \
    constexpr ClassName(Exp0 a, Exp1 b) : m_a{a}, m_b{b} {} \
    constexpr auto val() { return Func($(m_a), $(m_b)); } \
    virtual Str toString() const { \
        Str s{Str1}; \
        s += conv2str(m_a); \
        s += Str2; \
        s += conv2str(m_b); \
        s += Str3; \
        return s; \
    } \
    friend std::ostream &operator<<(std::ostream &output, const ClassName& obj) { \
        output << obj.toString(); \
        return output; \
    } \
    constexpr Exp0 first() { return m_a; } \
    constexpr Exp1 second() { return m_b; } \
}; \

#define DECL_OPR_2(Name, Opr) \
template<typename T0, typename T1> constexpr auto Name##Func(T0 a, T1 b) { return a Opr b; } \
DECL_OPR_CLASS_2(Name, Name##Func, "(", " " #Opr " ", ")") \
template<typename T0, typename T1> \
constexpr Name<Var<T0>*, Var<T1>*> operator Opr(Var<T0>& a, Var<T1>& b) \
{ return {&a, &b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name<Var<T>*,Exp<A,B>> operator Opr(Var<T>& a, Exp<A,B> b) \
{ return {&a, b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name<Exp<A,B>,Var<T>*> operator Opr(Exp<A,B> a, Var<T>& b) \
{ return {a, &b}; } \
template<typename A, typename B, \
         typename C, typename D, \
         template<class...> class Exp0, \
         template<class...> class Exp1> \
constexpr Name<Exp0<A,B>,Exp1<C,D>> operator Opr(Exp0<A,B> a, Exp1<C,D> b) \
{ return {a, b}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name<Exp0<A,B>,Const<T,DummyClass>> operator Opr(Exp0<A,B> a, T b) \
{ return {a, Const{b}}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name<Const<T,DummyClass>,Exp0<A,B>> operator Opr(T a, Exp0<A,B> b) \
{ return {Const{a}, b}; } \
template<typename T0, typename T1> \
constexpr Name<Const<T0,DummyClass>,Var<T1>*> operator Opr(T0 a, Var<T1>& b) \
{ return {Const{a}, &b}; } \
template<typename T0, typename T1> \
constexpr Name<Var<T0>*,Const<T1,DummyClass>> operator Opr(Var<T0>& a, T1 b) \
{ return {&a, Const{b}}; } \

#define DECL_FUNC_2(Name, Func) \
DECL_OPR_CLASS_2(Name, Func, #Func "( ", ", ", " )") \
template<typename T0, typename T1> \
constexpr Name<Var<T0>*, Var<T1>*> Func(Var<T0>& a, Var<T1>& b) \
{ return {&a, &b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name<Var<T>*,Exp<A,B>> Func(Var<T>& a, Exp<A,B> b) \
{ return {&a, b}; } \
template<typename T, typename A, typename B, \
         template<class...> class Exp> \
constexpr Name<Exp<A,B>,Var<T>*> Func(Exp<A,B> a, Var<T>& b) \
{ return {a, &b}; } \
template<typename A, typename B, \
         typename C, typename D, \
         template<class...> class Exp0, \
         template<class...> class Exp1> \
constexpr Name<Exp0<A,B>,Exp1<C,D>> Func(Exp0<A,B> a, Exp1<C,D> b) \
{ return {a, b}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name<Exp0<A,B>,Const<T,DummyClass>> Func(Exp0<A,B> a, T b) \
{ return {a, Const{b}}; } \
template<typename A, typename B, \
         template<class...> class Exp0, \
         typename T> \
constexpr Name<Const<T,DummyClass>,Exp0<A,B>> Func(T a, Exp0<A,B> b) \
{ return {Const{a}, b}; } \
template<typename T0, typename T1> \
constexpr Name<Const<T0,DummyClass>,Var<T1>*> Func(T0 a, Var<T1>& b) \
{ return {Const{a}, &b}; } \
template<typename T0, typename T1> \
constexpr Name<Var<T0>*,Const<T1,DummyClass>> Func(Var<T0>& a, T1 b) \
{ return {&a, Const{b}}; } \

#define DECL_OPR_1(Name, Opr) \
template<typename T> constexpr auto Name##Func(T a) { return Opr a; } \
DECL_OPR_CLASS_1(Name, Name##Func, "( " #Opr, " )") \
template<typename T> \
constexpr Name<Var<T>*,DummyClass> operator Opr(Var<T>& a) \
{ return {&a}; } \
template<typename A, typename B, \
         template<class...> class Exp> \
constexpr Name<Exp<A,B>,DummyClass> operator Opr(Exp<A,B> a) \
{ return {a}; } \

#define DECL_FUNC_1(Name, Func) \
DECL_OPR_CLASS_1(Name, Func, #Func "( ", " )") \
template<typename T> \
constexpr Name<Var<T>*,DummyClass> Func(Var<T>& a) \
{ return {&a}; } \
template<typename A, typename B, \
         template<class...> class Exp> \
constexpr Name<Exp<A,B>,DummyClass> Func(Exp<A,B> a) \
{ return {a}; } \

DECL_OPR_2(Add,+)
DECL_OPR_2(Sub,-)
DECL_OPR_2(Mul,*)
DECL_OPR_2(Div,/)
DECL_OPR_1(Neg,-)
DECL_OPR_1(Pos,+)
DECL_FUNC_1(AbsExp, Abs)
DECL_FUNC_1(SqrtExp, Sqrt)
DECL_FUNC_1(CosExp, Cos)
DECL_FUNC_1(SinExp, Sin)
DECL_FUNC_1(TanExp, Tan)
DECL_FUNC_1(ACosExp, ACos)
DECL_FUNC_1(ASinExp, ASin)
DECL_FUNC_1(ATanExp, ATan)
DECL_FUNC_2(ATan2Exp, ATan2)

/* Addition with ZeroExp */
template<typename T0, typename T1>
constexpr auto operator+(Var<T0>& a, ZeroExp<T1> b) { return a; }
template<typename T0, typename T1>
constexpr auto operator+(ZeroExp<T0> a, Var<T1>& b) { return b; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator+(Exp<A,B> a, ZeroExp<T> b) { return a; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator+(ZeroExp<T> a, Exp<A,B> b) { return b; }
template<typename T0, typename T1>
constexpr auto operator+(ZeroExp<T0> a, ZeroExp<T1> b) { return a; }

/* Subtraction with ZeroExp */
template<typename T0, typename T1>
constexpr auto operator-(Var<T0>& a, ZeroExp<T1> b) { return a; }
template<typename T0, typename T1>
constexpr auto operator-(ZeroExp<T0> a, Var<T1>& b) { return -b; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator-(Exp<A,B> a, ZeroExp<T> b) { return a; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator-(ZeroExp<T> a, Exp<A,B> b) { return -b; }
template<typename T0, typename T1>
constexpr auto operator-(ZeroExp<T0> a, ZeroExp<T1> b) { return a; }

/* Multiplication by ZeroExp */
template<typename T0, typename T1>
constexpr auto operator*(Var<T0>& a, ZeroExp<T1> b) { return b; }
template<typename T0, typename T1>
constexpr auto operator*(ZeroExp<T0> a, Var<T1>& b) { return a; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator*(Exp<A,B> a, ZeroExp<T> b) { return b; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator*(ZeroExp<T> a, Exp<A,B> b) { return a; }
template<typename T0, typename T1>
constexpr auto operator*(ZeroExp<T0> a, ZeroExp<T1> b) { return a; }

/* Division where ZeroExp is a numerator */
template<typename T0, typename T1>
constexpr auto operator/(ZeroExp<T0> a, Var<T1>& b) { return a; }
template<typename A, typename B, template<class...> class Exp, typename T>
constexpr auto operator/(ZeroExp<T> a, Exp<A,B> b) { return a; }

template<class T> constexpr auto $(T&& v) { return v.val(); }
template<class T> constexpr auto $(T* v) { return v->val(); }

} // namespace frogs

#endif // _FROGS_EXPRESSIONS_H
