#ifndef _FROGS_VECTOR_H
#define _FROGS_VECTOR_H

#include <vector>
#include <array>
#include <cassert>

namespace frogs
{

/* This is a generic class for vectors */
template<typename T, std::uint8_t N>
class Vector
{
protected:
    T m_data[N];

public:
    constexpr Vector()
    {
        for (std::uint8_t i = 0 ; i < N ; i++)
            m_data[i] = Zero(T{});
    }

    constexpr Vector(const T(&list)[N])
    {
        for (std::uint8_t i = 0 ; i < N ; i++)
            m_data[i] = list[i];
    }

    constexpr T& operator[](std::uint8_t index)
    {
        assert(index < N);
        return m_data[index%N];
    }

    constexpr T operator[](std::uint8_t index) const
    {
        assert(index < N);
        return m_data[index%N];
    }

    constexpr T& operator()(std::uint8_t index) { return (*this)[index]; }
    constexpr T operator()(std::uint8_t index) const { return (*this)[index]; }

    Str toString() const
    {
        Str s = "[";
        for (std::int8_t i = 0 ; i < N-1 ; i++)
            s += conv2str(m_data[i]) + ", ";
        s += conv2str(m_data[N-1]) + "]";
        return s;
    }

    friend std::ostream &operator<<(std::ostream &output, const Vector& obj)
    {
        output << obj.toString();
        return output;
    }

    friend std::ostream &operator<<(std::ostream &output, const Vector&& obj)
    {
        output << obj.toString();
        return output;
    }

    constexpr Vector<Real,N> normalized();

    constexpr std::uint8_t size() { return N; }
};

template<typename T> class Vec3;
template<typename T> class Vec4;

/* A specific class for a vectors with 2 elements */
template<typename T>
class Vec2 : public Vector<T,2>
{
public:
    constexpr Vec2(const T(&list)[2]) : Vector<T,2>{list} {}
    constexpr Vec2(T x = Zero(T{}),
                   T y = Zero(T{}))
                   : Vector<T,2>{{x, y}} {}
    constexpr Vec2(Vector<T,2> xy)
                   : Vector<T,2>{{xy[0], xy[1]}} {}
    constexpr T& x() { return (*this)[0]; }
    constexpr T& y() { return (*this)[1]; }
    constexpr T x() const { return (*this)[0]; }
    constexpr T y() const { return (*this)[1]; }

    constexpr Vec3<T> operator,(T other);
    constexpr Vec4<T> operator,(Vec2<T> other);
};

/* A specific class for a vectors with 3 elements */
template<typename T>
class Vec3 : public Vector<T,3>
{
public:
    constexpr Vec3(const T(&list)[3]) : Vector<T,3>{list} {}
    constexpr Vec3(T x = Zero(T{}),
                   T y = Zero(T{}),
                   T z = Zero(T{}))
                   : Vector<T,3>{{x, y, z}} {}
    constexpr Vec3(Vector<T,2> xy,
                   T z = Zero(T{}))
                   : Vector<T,3>{{xy[0], xy[1], z}} {}
    constexpr Vec3(T x, Vector<T,2> yz)
                   : Vector<T,3>{{x, yz[0], yz[1]}} {}
    constexpr Vec3(Vector<T,3> xyz)
                   : Vector<T,3>{{xyz[0], xyz[1], xyz[2]}} {}
    constexpr T& x() { return (*this)[0]; }
    constexpr T& y() { return (*this)[1]; }
    constexpr T& z() { return (*this)[2]; }
    constexpr T x() const { return (*this)[0]; }
    constexpr T y() const { return (*this)[1]; }
    constexpr T z() const { return (*this)[2]; }

    constexpr Vec4<T> operator,(T other);
};

/* A specific class for a vectors with 4 elements */
template<typename T>
class Vec4 : public Vector<T,4>
{
public:
    constexpr Vec4(const T(&list)[4]) : Vector<T,4>{list} {}
    constexpr Vec4(T x = Zero(T{}),
                   T y = Zero(T{}),
                   T z = Zero(T{}),
                   T w = Zero(T{}))
                   : Vector<T,4>{{x, y, z, w}} {}
    constexpr Vec4(Vector<T,2> xy, T z = Zero(T{}), T w = Zero(T{}))
                   : Vector<T,4>{{xy[0], xy[1], z, w}} {}
    constexpr Vec4(Vector<T,2> xy, Vector<T,2> zw)
                   : Vector<T,4>{{xy[0], xy[1], zw[0], zw[1]}} {}
    constexpr Vec4(T x, Vector<T,2> yz, T w = Zero(T{}))
                   : Vector<T,4>{{x, yz[0], yz[1], w}} {}
    constexpr Vec4(T x, T y, Vector<T,2> zw)
                   : Vector<T,4>{{x, y, zw[0], zw[1]}} {}
    constexpr Vec4(T x, Vector<T,3> yzw)
                   : Vector<T,4>{{x, yzw[0], yzw[1], yzw[2]}} {}
    constexpr Vec4(Vector<T,3> xyz, T w = Zero(T{}))
                   : Vector<T,4>{{xyz[0], xyz[1], xyz[2], w}} {}
    constexpr Vec4(Vector<T,4> xyzw)
                   : Vector<T,4>{{xyzw[0], xyzw[1], xyzw[2], xyzw[3]}} {}
    constexpr T& x() { return (*this)[0]; }
    constexpr T& y() { return (*this)[1]; }
    constexpr T& z() { return (*this)[2]; }
    constexpr T& w() { return (*this)[3]; }
    constexpr T x() const { return (*this)[0]; }
    constexpr T y() const { return (*this)[1]; }
    constexpr T z() const { return (*this)[2]; }
    constexpr T w() const { return (*this)[3]; }
};

template<typename T>
constexpr Vec3<T> Vec2<T>::operator,(T other) { return Vec3{*this, other}; }
template<typename T>
constexpr Vec4<T> Vec2<T>::operator,(Vec2<T> other) { return Vec4{*this, other}; }
template<typename T>
constexpr Vec4<T> Vec3<T>::operator,(T other) { return Vec4{*this, other}; }

/*
 * If someone wants to use the word "Vec" instead of specifiying
 * the number, they can use these functions to create the vector.
 */

template<typename T> constexpr auto Vec(T x, T y) { return Vec2{x, y}; }

template<typename T> constexpr auto Vec(T x, T y, T z) { return Vec3{x, y, z}; }
template<typename T> constexpr auto Vec(Vector<T,2> xy, T z) { return Vec3{xy, z}; }
template<typename T> constexpr auto Vec(T x, Vector<T,2> yz) { return Vec3{x, yz}; }

template<typename T> constexpr auto Vec(T x, T y, T z, T w) { return Vec4{x, y, z, w}; }
template<typename T> constexpr auto Vec(Vector<T,2> xy, T z, T w) { return Vec4{xy, z, w}; }
template<typename T> constexpr auto Vec(T x, Vector<T,2> yz, T w) { return Vec4{x, yz, w}; }
template<typename T> constexpr auto Vec(T x, T y, Vector<T,2> zw) { return Vec4{x, y, zw}; }
template<typename T> constexpr auto Vec(Vector<T,2> xy, Vector<T,2> zw) { return Vec4{xy, zw}; }
template<typename T> constexpr auto Vec(Vector<T,3> xyz, T w) { return Vec4{xyz, w}; }
template<typename T> constexpr auto Vec(T x, Vector<T,3> yzw) { return Vec4{x, yzw}; }

/* The add operators for vectors */

template<typename T, std::uint8_t N>
constexpr auto operator+(Vector<T,N>& v0, Vector<T,N>& v1)
{
    Vector<T,N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] + v1[i];
    return result;
}

template<typename T, std::uint8_t N>
constexpr auto operator+(Vector<T,N>&& v0, Vector<T,N>& v1)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v0[i] += v1[i];
    return v0;
}

template<typename T, std::uint8_t N>
constexpr auto operator+(Vector<T,N>&& v0, Vector<T,N>&& v1)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v0[i] += v1[i];
    return v0;
}

template<typename T, std::uint8_t N>
constexpr auto operator+(Vector<T,N>& v0, Vector<T,N>&& v1)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v1[i] += v0[i];
    return v1;
}

/* The subtract operators for vectors */

template<typename T, std::uint8_t N>
constexpr auto operator-(Vector<T,N>& v0, Vector<T,N>& v1)
{
    Vector<T,N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] - v1[i];
    return result;
}

template<typename T, std::uint8_t N>
constexpr auto operator-(Vector<T,N>&& v0, Vector<T,N>& v1)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v0[i] -= v1[i];
    return v0;
}

template<typename T, std::uint8_t N>
constexpr auto operator-(Vector<T,N>&& v0, Vector<T,N>&& v1)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v0[i] -= v1[i];
    return v0;
}

template<typename T, std::uint8_t N>
constexpr auto operator-(Vector<T,N>& v0, Vector<T,N>&& v1)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v1[i] -= v1[i];
    return v1;
}

/* The negative operators for vectors */

template<typename T, std::uint8_t N>
constexpr auto operator-(Vector<T,N>& v)
{
    Vector<T,N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = -v[i];
    return result;
}

template<typename T, std::uint8_t N>
constexpr auto operator-(Vector<T,N>&& v)
{
    for (std::uint8_t i = 0 ; i < N ; i++)
        v[i] = -v[i];
    return v;
}

/* The positive operators for vectors */

template<typename T, std::uint8_t N>
constexpr auto operator+(Vector<T,N>& v)
{
    return v;
}

template<typename T, std::uint8_t N>
constexpr auto operator+(Vector<T,N>&& v)
{
    return v;
}

/* The multiply operators for vectors */

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(Vector<T0,N>& v0, Vector<T1,N>& v1)
{
    Vector<decltype(std::declval<T0>*std::declval<T1>),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] * v1[0];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(Vector<T0,N>&& v0, Vector<T1,N>& v1)
{
    Vector<decltype(std::declval<T0>*std::declval<T1>),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] * v1[0];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(Vector<T0,N>& v0, Vector<T1,N>&& v1)
{
    Vector<decltype(std::declval<T0>*std::declval<T1>),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] * v1[0];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(Vector<T0,N>&& v0, Vector<T1,N>&& v1)
{
    Vector<decltype(std::declval<T0>*std::declval<T1>),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] * v1[0];
    return result;
}

/* The divide operators for vectors */

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator/(Vector<T0,N>& v0, Vector<T1,N>& v1)
{
    Vector<decltype(T0{}/T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] / v1[0];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator/(Vector<T0,N>&& v0, Vector<T1,N>& v1)
{
    Vector<decltype(T0{}/T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] / v1[0];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator/(Vector<T0,N>& v0, Vector<T1,N>&& v1)
{
    Vector<decltype(T0{}/T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] / v1[0];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator/(Vector<T0,N>&& v0, Vector<T1,N>&& v1)
{
    Vector<decltype(T0{}/T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v0[i] / v1[0];
    return result;
}

/* The scalar * vector operators */

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(T0 s, Vector<T1,N>& v)
{
    Vector<decltype(T0{}*T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = s * v[i];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(T0 s, Vector<T1,N>&& v)
{
    Vector<decltype(T0{}*T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = s * v[i];
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(Vector<T0,N>& v, T1 s)
{
    Vector<decltype(T0{}*T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v[i] * s;
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator*(Vector<T0,N>&& v, T1 s)
{
    Vector<decltype(T0{}*T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v[i] * s;
    return result;
}

/* The vector / scalar operators */

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator/(Vector<T0,N>& v, T1 s)
{
    Vector<decltype(T0{}/T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v[i] / s;
    return result;
}

template<typename T0, typename T1, std::uint8_t N>
constexpr auto operator/(Vector<T0,N>&& v, T1 s)
{
    Vector<decltype(T0{}/T1{}),N> result;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = v[i] / s;
    return result;
}

template<typename T, std::uint8_t N>
constexpr T Hypot(Vector<T,N>& v)
{
    auto total = Zero(T{}*T{});
    for (int i = 0 ; i < N ; i++)
        total += v[i] * v[i];
    return Sqrt(total);
}

template<typename T, std::uint8_t N> constexpr T Hypot(Vector<T,N>&& v) { return Hypot(fwd(v)); }

template<typename T, std::uint8_t N> constexpr T Dist(Vector<T,N>& a, Vector<T,N>& b) { return Hypot(b-a); }
template<typename T, std::uint8_t N> constexpr T Dist(Vector<T,N>&& a, Vector<T,N>& b) { return Hypot(b-a); }
template<typename T, std::uint8_t N> constexpr T Dist(Vector<T,N>& a, Vector<T,N>&& b) { return Hypot(b-a); }
template<typename T, std::uint8_t N> constexpr T Dist(Vector<T,N>&& a, Vector<T,N>&& b) { return Hypot(b-a); }

template<typename T, std::uint8_t N> constexpr Real Dot(Vector<T,N>& a, Vector<T,N>& b)
{
    Real result = 0.0;
    for (std::uint8_t i = 0 ; i < N ; i++)
        result += (a[i]/One(T{})) * (b[i]/One(T{}));
    return result;
}

template<typename T, std::uint8_t N> constexpr Real Dot(Vector<T,N>& a, Vector<T,N>&& b)
{ return Dot(a, fwd(b)); }
template<typename T, std::uint8_t N> constexpr Real Dot(Vector<T,N>&& a, Vector<T,N>& b)
{ return Dot(fwd(a), b); }
template<typename T, std::uint8_t N> constexpr Real Dot(Vector<T,N>&& a, Vector<T,N>&& b)
{ return Dot(fwd(a), fwd(b)); }

template<typename T, std::uint8_t N>
constexpr Vector<Real,N> Vector<T,N>::normalized()
{
    Vector<Real,N> result;
    auto len = Hypot(*this);
    for (std::uint8_t i = 0 ; i < N ; i++)
        result[i] = m_data[i] / len;
    return result;
}

} // namespace frogs

#endif // _FROGS_VECTOR_H
