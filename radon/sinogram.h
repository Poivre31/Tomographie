#pragma once
#include "projection_lerp.h"
#include "projection.h"

image sinogram(image data, double image_scale, size_t n_theta, size_t n_distance, double scale, double theta0)
{
    image result(n_distance, n_theta);
    ray _ray;
    for (size_t i = 0; i < n_theta; i++)
    {
        for (size_t j = 0; j < n_distance; j++)
        {
            double d = (j - n_distance / 2. + .5) * scale / (image_scale);
            double theta = 2 * M_PI * i / n_theta + theta0;
            _ray.set_from_distance_angle(d, theta);
            _ray.offset({data.width() / 2., data.height() / 2.});
            result.set(j + 1, i + 1, project(data, _ray) * image_scale / scale);
        }
    }
    return result;
}