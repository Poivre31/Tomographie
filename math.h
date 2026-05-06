#pragma once
#include <math.h>
#include <iostream>
#include <functional>

struct vec2
{
public:
    double x{};
    double y{};

    vec2() = default;

    vec2(double a) : x(a), y(a) {}

    vec2(double x, double y) : x(x), y(y) {}

    vec2 &operator=(const vec2 &v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }

    void zero()
    {
        x = {};
        y = {};
    }

    double norm() const
    {
        return std::sqrt(x * x + y * y);
    }

    void normalise()
    {
        double r = x * x + y * y;
        if (r == 0)
            return;
        r = 1. / sqrt(r);
        x *= r;
        y *= r;
    }

    void print() const
    {
        std::cout << "x: " << x << ", y: " << y << "\n";
    }

    bool operator==(const vec2 &v) const
    {
        return (x == v.x && y == v.y);
    }

    bool operator!=(const vec2 &v) const
    {
        return (x != v.x || y != v.y);
    }

    vec2 apply_element_wise(std::function<double(double)> func)
    {
        return vec2(func(x), func(y));
    }

    friend vec2 operator*(double a, const vec2 &v)
    {
        vec2 out;
        out.x = v.x * a;
        out.y = v.y * a;
        return out;
    }

    friend vec2 operator*(const vec2 &v, double a)
    {
        vec2 out;
        out.x = v.x * a;
        out.y = v.y * a;
        return out;
    }

    friend vec2 operator*(const vec2 &u, const vec2 &v)
    {
        vec2 out;
        out.x = u.x * v.x;
        out.y = u.y * v.y;
        return out;
    }

    vec2 &operator*=(double a)
    {
        x *= a;
        y *= a;
        return *this;
    }

    vec2 &operator*=(const vec2 &u)
    {
        x *= u.x;
        y *= u.y;
        return *this;
    }

    friend vec2 operator/(const vec2 &u, const vec2 &v)
    {
        vec2 out;
        out.x = u.x / v.x;
        out.y = u.y / v.y;
        return out;
    }

    friend vec2 operator/(const vec2 &u, double a)
    {
        vec2 out;
        double aInv = 1. / a;
        out.x = u.x * aInv;
        out.y = u.y * aInv;
        return out;
    }

    vec2 &operator/=(const vec2 &v)
    {
        x /= v.x;
        y /= v.y;
        return *this;
    }

    vec2 &operator/=(double a)
    {
        x = x / a;
        y = y / a;
        return *this;
    }

    friend vec2 operator+(const vec2 &u, const vec2 &v)
    {
        vec2 out;
        out.x = u.x + v.x;
        out.y = u.y + v.y;
        return out;
    }

    vec2 &operator+=(const vec2 &v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }

    friend vec2 operator-(const vec2 &u, const vec2 &v)
    {
        vec2 out;
        out.x = u.x - v.x;
        out.y = u.y - v.y;
        return out;
    }

    vec2 &operator-=(const vec2 &v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }

    vec2 operator-() const
    {
        vec2 out;
        out.x = -x;
        out.y = -y;
        return out;
    }
};