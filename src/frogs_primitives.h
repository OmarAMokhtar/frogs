#ifndef _FROGS_PRIMITIVES_H
#define _FROGS_PRIMITIVES_H

#include <string>
#include <math.h>

namespace frogs
{

using Integer = unsigned long long;
using Real = long double;
using Str = std::string;

template<class T> Str conv2str(T&& v) { return v.toString(); }
template<class T> Str conv2str(T* v) { return v->toString(); }
inline Str conv2str(double v) { return std::to_string(v); }
inline Str conv2str(Real v) { return std::to_string(v); }
inline Str conv2str(Integer v) { return std::to_string(v); }
inline Str conv2str(int v) { return std::to_string(v); }

inline auto Abs(double v) { return v < 0 ? -v : v; }
inline auto Abs(Real v) { return v < 0 ? -v : v; }
inline auto Abs(Integer v) { return v < 0 ? -v : v; }
inline auto Abs(int v) { return v < 0 ? -v : v; }

inline auto Sqrt(double v) { return sqrt(v); }
inline auto Sqrt(Real v) { return sqrt(v); }
inline auto Sqrt(Integer v) { return sqrt(v); }
inline auto Sqrt(int v) { return sqrt(v); }

} // namespace frogs

#endif // _FROGS_PRIMITIVES_H
