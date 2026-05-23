#pragma once
#include <tuple>
#include <cmath>

std::tuple<size_t, size_t, size_t, size_t, double, double, double, double> bilinear_weights(image im, double x, double y)
{
    size_t x1 = floor(x);
    size_t y1 = floor(y);
    size_t x2 = round(x1 + round(std::copysign(1, x - x1)));
    size_t y2 = round(y1 + round(std::copysign(1, y - y1)));
    if (x2 < x1)
        std::swap(x1, x2);
    if (y2 < y1)
        std::swap(y1, y2);
    // x2 = std::clamp(x2, (size_t)1, im.width());
    // y2 = std::clamp(y2, (size_t)1, im.height());

    double W = (x2 - x1) * (y2 - y1);
    double w11 = (x2 - x) * (y2 - y) / W;
    double w12 = (x2 - x) * (y - y1) / W;
    double w21 = (x - x1) * (y2 - y) / W;
    double w22 = (x - x1) * (y - y1) / W;
    return std::make_tuple(x1, x2, y1, y2, w11, w12, w21, w22);
}

double bilinear_interpolation(image im, double x, double y)
{
    auto [x1, x2, y1, y2, w11, w12, w21, w22] = bilinear_weights(im, x, y);
    return w11 * im.get(x1, y1) + w12 * im.get(x1, y2) + w21 * im.get(x2, y1) + w22 * im.get(x2, y2);
}