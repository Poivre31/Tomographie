#pragma once
#include "projection.h"

image sinogram(image data, size_t n_theta, size_t n_distance, double d_max)
{
    image result(n_distance, n_theta);
    ray _ray;
    for (size_t i = 0; i < n_theta; i++)
    {
        for (size_t j = 0; j < n_distance; j++)
        {
            double d = (2. * j - n_distance) * d_max / (n_distance - 1);
            double theta = 2 * M_PI * i / n_theta;
            _ray.set_from_distance_angle(d, theta);
            _ray.offset({data.width() / 2., data.height() / 2.});
            result.set(j + 1, i + 1, project(data, _ray));
        }
    }
    return result;
}