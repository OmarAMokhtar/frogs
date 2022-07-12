#ifndef _FROGS_PRIMITIVES_H
#define _FROGS_PRIMITIVES_H

#include <string>
#include <math.h>

namespace frogs
{

using Integer = unsigned long long;
using Real = double;
using Str = std::string;

template<class T> Str conv2str(T&& v) { return v.toString(); }
template<class T> Str conv2str(T* v) { return v->toString(); }
Str conv2str(Real v);

inline Str conv2str(Integer v) { return std::to_string(v); }
inline Str conv2str(int v) { return std::to_string(v); }

inline auto Abs(Real v) { return v < 0 ? -v : v; }
inline auto Abs(Integer v) { return v < 0 ? -v : v; }
inline auto Abs(int v) { return v < 0 ? -v : v; }

inline auto Sqrt(Real v) { return sqrt(v); }
inline auto Sqrt(Integer v) { return sqrt(v); }
inline auto Sqrt(int v) { return sqrt(v); }

constexpr Real One(Real) { return 1.0; }
constexpr Real Zero(Real) { return 0.0; }
constexpr Integer One(Integer) { return 1; }
constexpr Integer Zero(Integer) { return 0; }
constexpr int One(int) { return 1; }
constexpr int Zero(int) { return 0; }

inline Str operator+(Str a, Str b)
{
    Str result = a;
    result += b;
    return result;
}

inline Str operator+(Str a, const char* b)
{
    Str result = a;
    result += b;
    return result;
}

inline Str operator+(const char* a, Str b)
{
    Str result = a;
    result += b;
    return result;
}

template<typename T>
constexpr T& fwd(T&& v) { return std::forward<T&>(v); };

} // namespace frogs

#endif // _FROGS_PRIMITIVES_H
