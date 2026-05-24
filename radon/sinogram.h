#pragma once
#include "projection.h"

inline image sinogram(image data, double image_scale, size_t n_theta, size_t n_distance, double scale)
{
    image result(n_distance, n_theta);
    ray _ray;
    for (size_t i = 0; i < n_theta; i++)
    {
        std::cout << "\r\33[KComputing sinogram: image projections (" << round(100. * i / (n_theta - 1)) << "%)" << std::flush;

        for (size_t j = 0; j < n_distance; j++)
        {
            double d = (j - n_distance / 2. + .5) * scale / (image_scale);
            double theta = 2 * M_PI * i / n_theta;
            _ray.set_from_distance_angle(d, theta);
            _ray.offset({data.width() / 2., data.height() / 2.});
            result.set(j + 1, i + 1, project(data, _ray) * image_scale / scale);
        }
    }
    std::cout << std::endl;
    return result;
}