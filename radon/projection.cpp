#include "projection.h"

std::vector<double> grid_intersects(size_t width, size_t height, ray r)
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
            return distances;

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
                return distances;
        }
        else // then (r.direction().x == 0)
        {
            if (r.origin().x >= 0 && r.origin().x <= width)
            {
                intersect_1 = vec2(r.origin().x, 0);
                intersect_2 = vec2(r.origin().x, height);
            }
            else
                return distances;
        }
    }

    std::vector<double> horizontal;
    for (size_t y = ceil(std::min(intersect_1.y, intersect_2.y)); y <= floor(std::max(intersect_1.y, intersect_2.y)); y++)
    {
        horizontal.push_back(r.x_intersect_distance(y));
    }
    std::vector<double> vertical;
    for (size_t x = ceil(std::min(intersect_1.x, intersect_2.x)); x <= floor(std::max(intersect_1.x, intersect_2.x)); x++)
    {
        vertical.push_back(r.y_intersect_distance(x));
    }
    if (!std::is_sorted(horizontal.begin(), horizontal.end()))
        std::reverse(horizontal.begin(), horizontal.end());
    if (!std::is_sorted(vertical.begin(), vertical.end()))
        std::reverse(vertical.begin(), vertical.end());
    distances.resize(horizontal.size() + vertical.size());
    std::merge(horizontal.begin(), horizontal.end(), vertical.begin(), vertical.end(), distances.begin());
    return distances;
}

double project(image &im, ray r)
{
    auto distances = grid_intersects(im.width(), im.height(), r);
    if (distances.size() == 0)
        return 0.;

    timer::continue_watch("project");
    double integral = 0;
    for (size_t i = 0; i < distances.size() - 1; i++)
    {
        vec2 xy = r.at_distance((distances[i] + distances[i + 1]) * .5);
        size_t x = floor(xy.x);
        size_t y = floor(xy.y);

        integral += (distances[i + 1] - distances[i]) * im.get(x, y);
    }
    timer::pause_watch("project");

    return integral;
}