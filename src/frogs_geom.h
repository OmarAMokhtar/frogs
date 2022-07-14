#ifndef _FROGS_GEOM_H
#define _FROGS_GEOM_H

#include "frogs_matrix.h"
#include "frogs_physical_types.h"
#include "frogs_utils.h"
#include <vector>
#include <tuple>

namespace frogs
{

class Line2D
{
private:
    Vec2<Distance<1>> m_p0;
    Vec2<Distance<1>> m_p1;

public:
    constexpr Line2D() = default;

    constexpr Line2D(Vec2<Distance<1>>& p0, Vec2<Distance<1>>& p1)
                    : m_p0{p0}, m_p1{p1} {}

    constexpr Line2D(Vec2<Distance<1>>& p0, Vec2<Distance<1>>&& p1)
                    : m_p0{p0}, m_p1{p1} {}

    constexpr Line2D(Vec2<Distance<1>>&& p0, Vec2<Distance<1>>& p1)
                    : m_p0{p0}, m_p1{p1} {}

    constexpr Line2D(Vec2<Distance<1>>&& p0, Vec2<Distance<1>>&& p1)
                    : m_p0{p0}, m_p1{p1} {}

    constexpr Line2D(Distance<1> x0, Distance<1> y0, Distance<1> x1, Distance<1> y1)
                    : m_p0{x0,y0}, m_p1{x1,y1} {}

    constexpr auto p0() const { return m_p0; }
    constexpr auto p1() const { return m_p1; }
    constexpr auto x0() const { return m_p0.x(); }
    constexpr auto y0() const { return m_p0.y(); }
    constexpr auto x1() const { return m_p1.x(); }
    constexpr auto y1() const { return m_p1.y(); }
    constexpr Distance<1> dx() const { return m_p1.x() - m_p0.x(); }
    constexpr Distance<1> dy() const { return m_p1.y() - m_p0.y(); }
    constexpr Angle<1> angle() const { return ATan2(dy(),dx()); }
    constexpr Distance<1> length() const { return Dist(p0(),p1()); }

    void setAngle(Angle<1> ang) { rotate(ang - angle()); }

    void rotate(Angle<1> ang)
    {
        Mat4 mat;
        mat.translate(-x0(), -y0());
        mat.rotate(ang, 0, 0, 1);
        mat.translate(x0(), y0());
        *this = mat * (*this);
    }

    void setLength(Distance<1> len) { scale(len/length()); }

    void scale(Real factor)
    {
        Mat4 mat;
        mat.translate(-x0(), -y0());
        mat.scale(factor);
        mat.translate(x0(), y0());
        *this = mat * (*this);
    }

    friend Line2D operator*(Mat4& m, Line2D& l)
    {
        auto newP0 = m * l.m_p0;
        auto newP1 = m * l.m_p1;
        return {newP0.x(), newP0.y(), newP1.x(), newP1.y()};
    }

    friend Line2D operator*(Mat4& m, Line2D&& l) { return m * fwd(l); }
    friend Line2D operator*(Mat4&& m, Line2D& l) { return fwd(m) * l; }
    friend Line2D operator*(Mat4&& m, Line2D&& l) { return fwd(m) * fwd(l); }

    friend std::tuple<bool, Vec2<Distance<1>>> Intersect(const Line2D& l0, const Line2D& l1)
    {
        auto dx0 = l0.dx();
        auto dy0 = l0.dy();
        auto dx1 = l1.dx();
        auto dy1 = l1.dy();

        auto ix = 0_m;
        auto iy = 0_m;

        if (Abs(dx0) > Abs(dy0))
        {
            auto m0 = dy0/dx0;
            auto b0 = l0.y0() - m0*l0.x0();
            if (Abs(dx1) > Abs(dy1))
            {
                auto m1 = dy1/dx1;
                auto b1 = l1.y0() - m1*l1.x0();
                ix = (b0-b1)/(m1-m0);
                iy = m0*ix+b0;
            }
            else
            {
                auto m1 = dx1/dy1;
                auto b1 = l1.x0() - m1*l1.y0();
                ix = (-b0*m1-b1)/(m1*m0-1.0);
                iy = ix*m0+b0;
            }
        }
        else
        {
            auto m0 = dx0/dy0;
            auto b0 = l0.x0() - m0*l0.y0();
            if (Abs(dx1) > Abs(dy1))
            {
                auto m1 = dy1/dx1;
                auto b1 = l1.y0() - m1*l1.x0();
                ix = (-b1*m0-b0)/(m0*m1-1.0);
                iy = ix*m1+b1;
            }
            else
            {
                auto m1 = dx1/dy1;
                auto b1 = l1.x0() - m1*l1.y0();
                iy = (b0-b1)/(m1-m0);
                ix = iy*m0+b0;
            }
        }

        return std::make_tuple(
            (In(ix, Range{l0.x0(),l0.x1()}) &&
                In(iy, Range{l0.y0(),l0.y1()}) &&
                In(ix, Range{l1.x0(),l1.x1()}) &&
                In(iy, Range{l1.y0(),l1.y1()})),
                (ix, iy));
    }

    friend std::tuple<bool, Vec2<Distance<1>>> Intersect(const Line2D& l0, const Line2D&& l1)
    { return Intersect(l0,fwd(l1)); }
    friend std::tuple<bool, Vec2<Distance<1>>> Intersect(const Line2D&& l0, const Line2D& l1)
    { return Intersect(fwd(l0),l1); }
    friend std::tuple<bool, Vec2<Distance<1>>> Intersect(const Line2D&& l0, const Line2D&& l1)
    { return Intersect(fwd(l0),fwd(l1)); }

    friend bool IsLeft(Vec2<Distance<1>>& pt, Line2D& line)
    {
        Mat4 mat;
        mat.translate(-line.x0(), -line.y0());
        mat.rotate(-line.angle(), 0, 0, 1);
        return ((mat * pt).y() > 0_m);
    }

    friend bool IsLeft(Vec2<Distance<1>>& pt, Line2D&& line)
    { return IsLeft(pt, fwd(line)); }
    friend bool IsLeft(Vec2<Distance<1>>&& pt, Line2D& line)
    { return IsLeft(fwd(pt), line); }
    friend bool IsLeft(Vec2<Distance<1>>&& pt, Line2D&& line)
    { return IsLeft(fwd(pt), fwd(line)); }
};

class Shape2D
{
private:
    std::vector<Vec2<Distance<1>>> m_data;

public:
    Shape2D() = default;

    auto begin() { return m_data.begin(); }
    auto end() { return m_data.end(); }

    auto begin() const { return m_data.begin(); }
    auto end() const { return m_data.end(); }

    Shape2D& operator<<(Vec2<Distance<1>>& pt) { m_data.push_back(pt); return *this; }
    Shape2D& operator<<(Vec2<Distance<1>>&& pt) { m_data.push_back(pt); return *this; }

    Shape2D& operator<<(Shape2D& s)
    {
        for (auto& pt : s)
            m_data.push_back(pt);
        return *this;
    }

    Shape2D& operator<<(Shape2D&& s)
    {
        for (auto& pt : s)
            m_data.push_back(pt);
        return *this;
    }

    friend Shape2D operator*(Mat4& m, Shape2D& s)
    {
        Shape2D result;
        for (auto& pt : s)
        {
            auto newPt = m * pt;
            result << (newPt[0], newPt[1]);
        }
        return result;
    }

    friend Shape2D operator*(Mat4& m, Shape2D&& s)
    {
        for (auto& pt : s)
        {
            auto newPt = m * pt;
            pt = (newPt[0], newPt[1]);
        }
        return s;
    }

    friend Shape2D operator*(Mat4&& m, Shape2D& s) { return fwd(m) * s; }
    friend Shape2D operator*(Mat4&& m, Shape2D&& s) { return fwd(m) * s; }

    Str toString() const
    {
        Str s = "[ ";
        for (auto& pt : m_data)
            s += conv2str(pt);
        s += " ]";
        return s;
    }

    friend std::ostream &operator<<(std::ostream &output, const Shape2D& obj)
    {
        output << obj.toString();
        return output;
    }

    friend std::ostream &operator<<(std::ostream &output, const Shape2D&& obj)
    {
        output << obj.toString();
        return output;
    }
};

} // namespace frogs

#endif // _FROGS_GEOM_H
