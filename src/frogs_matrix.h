#ifndef _FROGS_MATRIX_H
#define _FROGS_MATRIX_H

#include "frogs_vector.h"
#include "frogs_physical_types.h"

namespace frogs
{

/* The matrix class */

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
class Matrix
{
protected:
    T m_data[Cols][Rows];

public:
    constexpr Matrix()
    {
        if constexpr (Rows == Cols)
            identity();
        else
            zeros();
    }

    constexpr Matrix(const Matrix<T,Rows,Cols>& m)
    {
        for (int i = 0 ; i < Cols ; i++)
            for (int j = 0 ; j < Rows ; j++)
                m_data[i][j] = m.m_data[i][j];
    }

    constexpr Matrix(const Matrix<T,Rows,Cols>&& m)
    {
        for (int i = 0 ; i < Cols ; i++)
            for (int j = 0 ; j < Rows ; j++)
                m_data[i][j] = m.m_data[i][j];
    }

    constexpr Matrix<T,Rows,Cols>& operator=(const Matrix<T,Rows,Cols>& m)
    {
        for (int i = 0 ; i < Cols ; i++)
            for (int j = 0 ; j < Rows ; j++)
                m_data[i][j] = m.m_data[i][j];
    }

    constexpr Matrix<T,Rows,Cols>& operator=(const Matrix<T,Rows,Cols>&& m)
    {
        for (int i = 0 ; i < Cols ; i++)
            for (int j = 0 ; j < Rows ; j++)
                m_data[i][j] = m.m_data[i][j];
    }

    constexpr void zeros()
    {
        for (int i = 0 ; i < Cols ; i++)
            for (int j = 0 ; j < Rows ; j++)
                m_data[i][j] = Zero(T{});
    }

    constexpr void identity()
    {
        for (int i = 0 ; i < Cols ; i++)
            for (int j = 0 ; j < Rows ; j++)
                m_data[i][j] = (i == j) ? One(T{}) : Zero(T{});
    }

    constexpr T& operator()(std::uint8_t row, std::uint8_t col)
    {
        assert(row < Rows && col < Cols);
        return m_data[col%Cols][row%Rows];
    }

    constexpr T operator()(std::uint8_t row, std::uint8_t col) const
    {
        assert(row < Rows && col < Cols);
        return m_data[col%Cols][row%Rows];
    }

    Str toString() const
    {
        Str s = "[";
        for (std::uint8_t i = 0 ; i < Rows ; i++)
        {
            s += "[";
            for (std::uint8_t j = 0 ; j < Cols-1 ; j++)
                s += conv2str(m_data[j][i]) + ", ";
            s += conv2str(m_data[Cols-1][i]) + "]";
            if (i < Rows-1)
                s += ", ";
        }
        s += "]";
        return s;
    }

    friend std::ostream &operator<<(std::ostream &output, const Matrix<T,Rows,Cols>& obj)
    {
        output << obj.toString();
        return output;
    }

    friend std::ostream &operator<<(std::ostream &output, const Matrix<T,Rows,Cols>&& obj)
    {
        output << obj.toString();
        return output;
    }
};

/* Some classes for special case matrices */

class Mat2 : public Matrix<Real,2,2>
{
public:
    constexpr Mat2() : Matrix<Real,2,2>{} {}

    constexpr Mat2(Real m00, Real m01,
                   Real m10, Real m11)
    {
        m_data[0][0] = m00;
        m_data[1][0] = m01;
        m_data[0][1] = m10;
        m_data[1][1] = m11;
    }

    constexpr Mat2(const Mat2& m) : Matrix<Real,2,2>{m} {}
    constexpr Mat2(const Mat2&& m) : Matrix<Real,2,2>{m} {}
};

class Mat3 : public Matrix<Real,3,3>
{
public:
    constexpr Mat3() : Matrix<Real,3,3>{} {}

    constexpr Mat3(Real m00, Real m01, Real m02,
                   Real m10, Real m11, Real m12,
                   Real m20, Real m21, Real m22)
    {
        m_data[0][0] = m00;
        m_data[1][0] = m01;
        m_data[2][0] = m02;
        m_data[0][1] = m10;
        m_data[1][1] = m11;
        m_data[2][1] = m12;
        m_data[0][2] = m20;
        m_data[1][2] = m21;
        m_data[2][2] = m22;
    }

    constexpr Mat3(const Mat3& m) : Matrix<Real,3,3>{m} {}
    constexpr Mat3(const Mat3&& m) : Matrix<Real,3,3>{m} {}
};

class Mat4 : public Matrix<Real,4,4>
{
public:
    constexpr Mat4() : Matrix<Real,4,4>{} {}

    constexpr Mat4(Matrix<Real,4,4>& mat)
    {
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                m_data[i][j] = mat(j,i);
    }

    constexpr Mat4(Matrix<Real,4,4>&& mat)
    {
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                m_data[i][j] = mat(j,i);
    }

    constexpr Mat4(const Mat4& mat)
    {
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                m_data[i][j] = mat(j,i);
    }

    constexpr Mat4(const Mat4&& mat)
    {
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                m_data[i][j] = mat(j,i);
    }

    constexpr Mat4& operator=(const Mat4& mat)
    {
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                m_data[i][j] = mat(j,i);
        return *this;
    }

    constexpr Mat4& operator=(const Mat4&& mat)
    {
        for (int i = 0 ; i < 4 ; i++)
            for (int j = 0 ; j < 4 ; j++)
                m_data[i][j] = mat(j,i);
        return *this;
    }

    constexpr Mat4(Real m00, Real m01, Real m02, Real m03,
                   Real m10, Real m11, Real m12, Real m13,
                   Real m20, Real m21, Real m22, Real m23,
                   Real m30, Real m31, Real m32, Real m33)
    {
        m_data[0][0] = m00;
        m_data[1][0] = m01;
        m_data[2][0] = m02;
        m_data[3][0] = m03;
        m_data[0][1] = m10;
        m_data[1][1] = m11;
        m_data[2][1] = m12;
        m_data[3][1] = m13;
        m_data[0][2] = m20;
        m_data[1][2] = m21;
        m_data[2][2] = m22;
        m_data[3][2] = m23;
        m_data[0][3] = m30;
        m_data[1][3] = m31;
        m_data[2][3] = m32;
        m_data[3][3] = m33;
    }

    /* The rotation function */
    void rotate(Angle angle, Real x, Real y, Real z);

    /* The actual translation function */
    void translate(Real x, Real y, Real z);

    /* Other overloads for translate */
    void translate(Distance x, Distance y, Distance z)
    { translate($(x).toMeters(), $(y).toMeters(), $(z).toMeters()); }
    void translate(Real x, Real y) { translate(x, y, 0.0); }
    void translate(Distance x, Distance y) { translate(x, y, 0_m); }
    void translate(Vector<Real,2>& v) { translate(v[0], v[1], 0.0); }
    void translate(Vector<Real,2>&& v) { translate(v[0], v[1], 0.0); }
    void translate(Vector<Distance,2>& v) { translate(v[0], v[1], 0_m); }
    void translate(Vector<Distance,2>&& v) { translate(v[0], v[1], 0_m); }
    void translate(Vector<Real,3>& v) { translate(v[0], v[1], v[2]); }
    void translate(Vector<Real,3>&& v) { translate(v[0], v[1], v[2]); }
    void translate(Vector<Distance,3>& v) { translate(v[0], v[1], v[2]); }
    void translate(Vector<Distance,3>&& v) { translate(v[0], v[1], v[2]); }
    void translate(Vector<Real,4>& v) { translate(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
    void translate(Vector<Real,4>&& v) { translate(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
    void translate(Vector<Distance,4>& v) { translate(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
    void translate(Vector<Distance,4>&& v) { translate(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
 
    /* The actual scale function */
    void scale(Real x, Real y, Real z);

    /* Other overloads for scale */
    void scale(Real s) { scale(s, s, s); }
    void scale(Vector<Real,2>& v) { scale(v[0], v[1], 1.0); }
    void scale(Vector<Real,2>&& v) { scale(v[0], v[1], 1.0); }
    void scale(Vector<Real,3>& v) { scale(v[0], v[1], v[2]); }
    void scale(Vector<Real,3>&& v) { scale(v[0], v[1], v[2]); }
    void scale(Vector<Real,4>& v) { scale(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
    void scale(Vector<Real,4>&& v) { scale(v[0]/v[3], v[1]/v[3], v[2]/v[3]); }
};

/* The matrix+matrix operators */

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator+(Matrix<T,Rows,Cols>& mat0, Matrix<T,Rows,Cols>& mat1)
{
    Matrix<T,Rows,Cols> result;
    for (std::uint8_t r = 0 ; r < Rows ; r++)
        for (std::uint8_t c = 0 ; c < Cols ; c++)
            result(r,c) = mat0(r,c) + mat1(r,c);
    return result;
}

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator+(Matrix<T,Rows,Cols>&& mat0, Matrix<T,Rows,Cols>& mat1)
{ return fwd(mat0) + mat1; }

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator+(Matrix<T,Rows,Cols>& mat0, Matrix<T,Rows,Cols>&& mat1)
{ return mat0 + fwd(mat1); }

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator+(Matrix<T,Rows,Cols>&& mat0, Matrix<T,Rows,Cols>&& mat1)
{ return fwd(mat0) + fwd(mat1); }

/* The matrix-matrix operators */

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator-(Matrix<T,Rows,Cols>& mat0, Matrix<T,Rows,Cols>& mat1)
{
    Matrix<T,Rows,Cols> result;
    for (std::uint8_t r = 0 ; r < Rows ; r++)
        for (std::uint8_t c = 0 ; c < Cols ; c++)
            result(r,c) = mat0(r,c) - mat1(r,c);
    return result;
}

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator-(Matrix<T,Rows,Cols>&& mat0, Matrix<T,Rows,Cols>& mat1)
{ return fwd(mat0) - mat1; }

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator-(Matrix<T,Rows,Cols>& mat0, Matrix<T,Rows,Cols>&& mat1)
{ return mat0 - fwd(mat1); }

template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator-(Matrix<T,Rows,Cols>&& mat0, Matrix<T,Rows,Cols>&& mat1)
{ return fwd(mat0) - fwd(mat1); }

/* The matrix*matrix operators */

template<typename T0, typename T1, std::uint8_t RowsLeft, std::uint8_t Common, std::uint8_t ColsRight>
constexpr auto operator*(Matrix<T0,RowsLeft,Common>& mat0, Matrix<T1,Common,ColsRight>& mat1)
{
    auto zero = Zero(T0{}*T1{});
    Matrix<decltype(T0{}*T1{}),RowsLeft,ColsRight> result;
    for (std::uint8_t r = 0 ; r < RowsLeft ; r++)
    {
        for (std::uint8_t c = 0 ; c < ColsRight ; c++)
        {
            result(r,c) = zero;
            for (std::uint8_t i = 0 ; i < Common ; i++)
                result(r,c) += mat0(i,c) * mat1(r,i);
        }
    }
    return result;
}

template<typename T0, typename T1, std::uint8_t RowsLeft, std::uint8_t Common, std::uint8_t ColsRight>
constexpr auto operator*(Matrix<T0,RowsLeft,Common>&& mat0, Matrix<T1,Common,ColsRight>& mat1)
{ return fwd(mat0) * mat1; }

template<typename T0, typename T1, std::uint8_t RowsLeft, std::uint8_t Common, std::uint8_t ColsRight>
constexpr auto operator*(Matrix<T0,RowsLeft,Common>& mat0, Matrix<T1,Common,ColsRight>&& mat1)
{ return mat0 * fwd(mat1); }

template<typename T0, typename T1, std::uint8_t RowsLeft, std::uint8_t Common, std::uint8_t ColsRight>
constexpr auto operator*(Matrix<T0,RowsLeft,Common>&& mat0, Matrix<T1,Common,ColsRight>&& mat1)
{ return fwd(mat0) * fwd(mat1); }

/* The vector*matrix operators */

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T0,Rows,Cols>& m, Vector<T1,Cols>& v)
{
    auto zero = Zero(T0{}*T1{});
    Vector<decltype(T0{}*T1{}),Cols> result;
    for (std::uint8_t c = 0 ; c < Cols ; c++)
    {
        result[c] = zero;
        for (std::uint8_t i = 0 ; i < Rows ; i++)
            result[c] += m(i,c) * v(i);
    }
    return result;
}

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T0,Rows,Cols>&& m, Vector<T1,Cols>& v)
{ return fwd(m) * v; }

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T0,Rows,Cols>& m, Vector<T1,Cols>&& v)
{ return m * fwd(v); }

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T0,Rows,Cols>&& m, Vector<T1,Cols>&& v)
{ return fwd(m) * fwd(v); }

/* If the vector is 3D or 2D, it would be good if we put default
 * values for z (0) and w (1) and multiply it with a 4x4 Matrix
 */

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>& m, Vector<T,3>& v)
{
    auto zero = Zero(T{});
    auto one = One(T{});
    return m * Vector<T,4>{v, one};
}

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>& m, Vector<T,2>& v)
{
    auto zero = Zero(T{});
    auto one = One(T{});
    return m * Vector<T,4>{v, zero, one};
}

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>& m, Vector<T,3>&& v)
{ return m * fwd(v); }

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>& m, Vector<T,2>&& v)
{ return m * fwd(v); }

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>&& m, Vector<T,3>&& v)
{ return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>&& m, Vector<T,2>&& v)
{ return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>&& m, Vector<T,3>& v)
{ return fwd(m) * v; }

template<typename T>
constexpr auto operator*(Matrix<Real,4,4>&& m, Vector<T,2>& v)
{ return fwd(m) * v; }

/* The scalar*matrix operators */

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T0,Rows,Cols>& m, T1 s)
{
    auto zero = Zero(T0{}*T1{});
    Vector<decltype(T0{}*T1{}),Cols> result;
    for (std::uint8_t c = 0 ; c < Cols ; c++)
        for (std::uint8_t r = 0 ; r < Rows ; r++)
            result(r,c) = s * m(r,c);
    return result;
}

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T0,Rows,Cols>&& m, T1 s)
{
    return fwd(m) * s;
}

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(T1 s, Matrix<T0,Rows,Cols>&& m)
{
    return fwd(m) * s;
}

template<typename T0, typename T1, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(T1 s, Matrix<T0,Rows,Cols>& m)
{
    return fwd(m) * s;
}

/* A special case function where if the scalar is a primitive real
 * number (which means no need to change the matrix type) and the
 * matrix happens to be an rvalue (which means it's ok to reuse its
 * memory), we just don't create another matrix.
 */
template<typename T, std::uint8_t Rows, std::uint8_t Cols>
constexpr auto operator*(Matrix<T,Rows,Cols>&& m, Real s)
{
    for (std::uint8_t c = 0 ; c < Cols ; c++)
        for (std::uint8_t r = 0 ; r < Rows ; r++)
            m(r,c) *= s;
    return m;
}

/* Special cases with Mat4 */

template<typename T>
constexpr auto operator*(Mat4& m, Vector<T,4>& v)
{
    return Vec4{ m(0,0) * v(0) + m(0,1) * v(1) + m(0,2) * v(2) + m(0,3) * v(3),
                 m(1,0) * v(0) + m(1,1) * v(1) + m(1,2) * v(2) + m(1,3) * v(3),
                 m(2,0) * v(0) + m(2,1) * v(1) + m(2,2) * v(2) + m(2,3) * v(3),
                 m(3,0) * v(0) + m(3,1) * v(1) + m(3,2) * v(2) + m(3,3) * v(3) };
}

template<typename T>
constexpr auto operator*(Mat4& m, Vector<T,3>& v)
{
    return Vec4{ m(0,0) * v(0) + m(0,1) * v(1) + m(0,2) * v(2) + m(0,3) * One(T{}),
                 m(1,0) * v(0) + m(1,1) * v(1) + m(1,2) * v(2) + m(1,3) * One(T{}),
                 m(2,0) * v(0) + m(2,1) * v(1) + m(2,2) * v(2) + m(2,3) * One(T{}),
                 m(3,0) * v(0) + m(3,1) * v(1) + m(3,2) * v(2) + m(3,3) * One(T{}) };
}

template<typename T>
constexpr auto operator*(Mat4& m, Vector<T,2>& v)
{
    return Vec4{ m(0,0) * v(0) + m(0,1) * v(1) + m(0,3) * One(T{}),
                 m(1,0) * v(0) + m(1,1) * v(1) + m(1,3) * One(T{}),
                 m(2,0) * v(0) + m(2,1) * v(1) + m(2,3) * One(T{}),
                 m(3,0) * v(0) + m(3,1) * v(1) + m(3,3) * One(T{}) };
}

template<typename T>
constexpr auto operator*(Mat4& m, Vector<T,4>&& v) { return m * fwd(v); }
template<typename T>
constexpr auto operator*(Mat4&& m, Vector<T,4>& v) { return fwd(m) * v; }
template<typename T>
constexpr auto operator*(Mat4&& m, Vector<T,4>&& v) { return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Mat4& m, Vector<T,3>&& v) { return m * fwd(v); }
template<typename T>
constexpr auto operator*(Mat4&& m, Vector<T,3>& v) { return fwd(m) * v; }
template<typename T>
constexpr auto operator*(Mat4&& m, Vector<T,3>&& v) { return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Mat4& m, Vector<T,2>&& v) { return m * fwd(v); }
template<typename T>
constexpr auto operator*(Mat4&& m, Vector<T,2>& v) { return fwd(m) * v; }
template<typename T>
constexpr auto operator*(Mat4&& m, Vector<T,2>&& v) { return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Mat4& m, Vec4<T>& v)
{
    return Vec4{ m(0,0) * v(0) + m(0,1) * v(1) + m(0,2) * v(2) + m(0,3) * v(3),
                 m(1,0) * v(0) + m(1,1) * v(1) + m(1,2) * v(2) + m(1,3) * v(3),
                 m(2,0) * v(0) + m(2,1) * v(1) + m(2,2) * v(2) + m(2,3) * v(3),
                 m(3,0) * v(0) + m(3,1) * v(1) + m(3,2) * v(2) + m(3,3) * v(3) };
}

template<typename T> constexpr auto operator*(Mat4&& m, Vec4<T>& v) { return fwd(m) * v; }
template<typename T> constexpr auto operator*(Mat4& m, Vec4<T>&& v) { return m * fwd(v); }
template<typename T> constexpr auto operator*(Mat4&& m, Vec4<T>&& v) { return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Mat4& m, Vec3<T>& v)
{
    return Vec4{ m(0,0) * v(0) + m(0,1) * v(1) + m(0,2) * v(2) + m(0,3) * One(T{}),
                 m(1,0) * v(0) + m(1,1) * v(1) + m(1,2) * v(2) + m(1,3) * One(T{}),
                 m(2,0) * v(0) + m(2,1) * v(1) + m(2,2) * v(2) + m(2,3) * One(T{}),
                 m(3,0) * v(0) + m(3,1) * v(1) + m(3,2) * v(2) + m(3,3) * One(T{}) };
}

template<typename T> constexpr auto operator*(Mat4&& m, Vec3<T>& v) { return fwd(m) * v; }
template<typename T> constexpr auto operator*(Mat4& m, Vec3<T>&& v) { return m * fwd(v); }
template<typename T> constexpr auto operator*(Mat4&& m, Vec3<T>&& v) { return fwd(m) * fwd(v); }

template<typename T>
constexpr auto operator*(Mat4& m, Vec2<T>& v)
{
    return Vec4{ m(0,0) * v(0) + m(0,1) * v(1) + m(0,3) * One(T{}),
                 m(1,0) * v(0) + m(1,1) * v(1) + m(1,3) * One(T{}),
                 m(2,0) * v(0) + m(2,1) * v(1) + m(2,3) * One(T{}),
                 m(3,0) * v(0) + m(3,1) * v(1) + m(3,3) * One(T{}) };
}

template<typename T> constexpr auto operator*(Mat4&& m, Vec2<T>& v) { return fwd(m) * v; }
template<typename T> constexpr auto operator*(Mat4& m, Vec2<T>&& v) { return m * fwd(v); }
template<typename T> constexpr auto operator*(Mat4&& m, Vec2<T>&& v) { return fwd(m) * fwd(v); }

constexpr auto operator*(Mat4& m0, Mat4& m1)
{
    Mat4 result;
    for (std::uint8_t r = 0 ; r < 4 ; r++)
    {
        for (std::uint8_t c = 0 ; c < 4 ; c++)
        {
            result(r,c) = 0.0;
            for (std::uint8_t i = 0 ; i < 4 ; i++)
                result(r,c) += m0(r,i) * m1(i,c);
        }
    }
    return result;
}

constexpr auto operator*(Mat4& m0, Mat4&& m1) { return m0 * fwd(m1); }
constexpr auto operator*(Mat4&& m0, Mat4& m1) { return fwd(m0) * m1; }
constexpr auto operator*(Mat4&& m0, Mat4&& m1) { return fwd(m0) * fwd(m1); }

void Mat4::rotate(Angle angle, Real x, Real y, Real z)
{
    auto c = Cos(angle);
    auto s = Sin(angle);
    auto ic = 1.0 - c;
    *this = Mat4{ x*x*ic+c,     x*y*ic-z*s,     x*z*ic+y*s,     0.0,
                  y*x*ic+z*s,   y*y*ic+c,       y*z*ic-x*s,     0.0,
                  x*z*ic-y*s,   y*z*ic+x*s,     z*z*ic+c,       0.0,
                  0.0,          0.0,            0.0,            1.0 } * (*this);
}

void Mat4::translate(Real x, Real y, Real z)
{
    *this = Mat4{ 1, 0, 0, x,
                  0, 1, 0, y,
                  0, 0, 1, z,
                  0, 0, 0, 1 } * (*this);
}

void Mat4::scale(Real x, Real y, Real z)
{
    *this = Mat4{ x, 0, 0, 0,
                  0, y, 0, 0,
                  0, 0, z, 0,
                  0, 0, 0, 1 } * (*this);
}

} // namespace frogs

#endif // _FROGS_MATRIX_H
