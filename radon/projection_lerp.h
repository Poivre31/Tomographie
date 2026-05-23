#pragma once
#include "ray.h"
#include "timer.h"
#include "bilinear_interp.h"

std::tuple<bool, vec2, vec2> boundary_intersects(size_t width, size_t height, ray r)
{
    std::vector<double> distances;
    vec2 intersect_1;
    vec2 intersect_2;

    // To refactor
    if (r.direction().x != 0 && r.direction().y != 0)
    {
        double x_top = r.at_distance(r.x_intersect_distance(0)).x;
        double x_bottom = r.at_distance(r.x_intersect_distance(height)).x;
        double y_left = r.at_distance(r.y_intersect_distance(0)).y;
        double y_right = r.at_distance(r.y_intersect_distance(width)).y;

        bool top = (x_top >= 0 && x_top <= width);
        bool bottom = (x_bottom >= 0 && x_bottom <= width);
        bool left = (y_left >= 0 && y_left <= height);
        bool right = (y_right >= 0 && y_right <= height);

        if (!(top || bottom || left || right))
            return std::make_tuple(false, vec2{}, vec2{});

        if (top)
            intersect_1 = vec2(x_top, 0);
        else if (bottom)
        {
            intersect_1 = vec2(x_bottom, height);
        }
        else if (left)
        {
            intersect_1 = vec2(0, y_left);
        }
        else if (right)
        {
            intersect_1 = vec2(width, y_right);
        }

        intersect_2 = intersect_1;

        if (top && vec2(x_top, 0) != intersect_1)
            intersect_2 = vec2(x_top, 0);
        else if (bottom && vec2(x_bottom, height) != intersect_1)
        {
            intersect_2 = vec2(x_bottom, height);
        }
        else if (left && vec2(0, y_left) != intersect_1)
        {
            intersect_2 = vec2(0, y_left);
        }
        else if (right && vec2(width, y_right) != intersect_1)
        {
            intersect_2 = vec2(width, y_right);
        }
    }
    else
    {
        if (r.direction().y == 0)
        {
            if (r.origin().y >= 0 && r.origin().y <= height)
            {
                intersect_1 = vec2(0, r.origin().y);
                intersect_2 = vec2(width, r.origin().y);
            }
            else
                return std::make_tuple(false, vec2{}, vec2{});
        }
        else // then (r.direction().x == 0)
        {
            if (r.origin().x >= 0 && r.origin().x <= width)
            {
                intersect_1 = vec2(r.origin().x, 0);
                intersect_2 = vec2(r.origin().x, height);
            }
            else
                return std::make_tuple(false, vec2{}, vec2{});
        }
    }
    return std::make_tuple(true, intersect_1, intersect_2);
}

/// @brief Computes the projection of the image along ray direction using trapezoidal integration on bilinearly interpolated points.
/// @param max_steps Number of integration steps along the longest path (the diagonal of the image), will be ajusted for shorter paths.
/// @return
double project_lerp(image &im, ray r, size_t max_steps)
{
    auto [intersect_found, intersect_1, intersect_2] = boundary_intersects(im.width(), im.height(), r);
    if (!intersect_found)
        return 0.;

    size_t N = max_steps * (intersect_2 - intersect_1).norm() / vec2{(double)im.height(), (double)im.width()}.norm();
    if (N <= 1)
        return 0.;
    double dl = (intersect_2 - intersect_1).norm() / (N - 1);

    timer::continue_watch("project");
    double integral = 0;
    for (size_t i = 0; i < N; i++)
    {
        vec2 xy = r.at_distance(i * dl);
        double value = bilinear_interpolation(im, xy.x, xy.y);
        integral += dl * value;
    }
    timer::pause_watch("project");

    return integral;
}