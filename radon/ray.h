#pragma once
#include "image.h"
#include <vector>
#include <algorithm>
#include <cmath>
#include "vec2.h"

struct vec2i
{
    size_t x;
    size_t y;
};

/// @brief A ray class containing origin and normalised direction vectors. The direction is normalised at construction.
class ray
{
public:
    ray()
    {
        _origin = {0., 0.};
        _dir = {1., 0.};
    }

    /// @brief Constructs the ray with `origin` and `dir/norm(dir)`. Error if `dir=0`.
    ray(vec2 origin, vec2 dir) : _origin(origin)
    {
        double d = dir.norm();
        if (d == 0)
            std::cout << "Invalid ray construction: direction vector is zero";
        else
            _dir = dir / d;
    }

    void offset(vec2 off)
    {
        _origin += off;
    }

    vec2 at_distance(double t) const
    {
        return _origin + t * _dir;
    }

    vec2 origin() const
    {
        return _origin;
    }

    vec2 direction() const
    {
        return _dir;
    }

    void set_from_distance_angle(double s, double theta)
    {
        _origin = {s * cos(theta), s * sin(theta)};
        _dir = {-sin(theta), cos(theta)};
    }

    double x_intersect_distance(double y_coord) const
    {
        if (_dir.y == 0.)
            return 0.;
        else
            return (y_coord - _origin.y) / _dir.y;
    }

    double y_intersect_distance(double x_coord) const
    {
        if (_dir.x == 0.)
            return 0.;
        else
            return (x_coord - _origin.x) / _dir.x;
    }

private:
    vec2 _origin;
    vec2 _dir;
};