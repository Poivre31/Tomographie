#pragma once

#include "image.h"
#include <vector>
#include <cmath>

struct vec2i
{
    size_t x;
    size_t y;
};

struct vec2
{
    double x;
    double y;
};

class ray
{
public:
    vec2 at_distance(double t)
    {
        return {origin.x + t * dir.x, origin.y + t * dir.y};
    }

    void set_distance_angle(double s, double theta)
    {
        origin = {s * cos(theta), s * sin(theta)};
        dir = {-cos(theta), -sin(theta)};
    }

private:
    vec2 origin;
    vec2 dir;
};

std::vector<vec2i>
a()
{
}

double
project(image im, ray r)
{

    double x_haut = 0;
}