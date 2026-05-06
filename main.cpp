#include <iostream>
#include "image.h"
#include "projection.h"
#include <functional>
#include <cmath>
#include "utility.h"
#include "my_fft.h"

timer t;

int main()
{
    size_t n = 1 << 24;
    size_t a = 32;
    std::vector<double> aperture(n);
    for (size_t i = 0; i < n; i++)
    {
        if (abs(i - n / 2.) < a)
            aperture[i] = 1;
        else
            aperture[i] = 0;
    }
    t.start_watch();
    auto datafft = fft_shift(modulo(fft(aperture)));
    t.print_ellapsed_time();

    // save_vector(aperture, "data1");
    // system("python ../display_plot.py data1.txt");
    // save_vector(datafft, "data2");
    // system("python ../display_plot.py data2.txt");

    return 0;

    size_t size = 512;
    image my_image(size, size);

    my_image.fill_rectangle(1. / (.8 * size), size / 2, size / 2, .8 * size, .8 * size);
    my_image.fill_ellipse(1, size / 2, size / 2, size / 4, size / 4);
    my_image.fill_phantom(size / 2, size / 2, .8 * size);
    my_image.save("img");

    ray my_ray({9, 32}, {2., 1.2});

    size_t n_theta = size;
    size_t n_s = size;
    image projection(n_theta, n_s);
    ray _ray;
    double s_max = size;
    for (size_t i = 0; i < n_theta; i++)
    {
        for (size_t j = 0; j < n_s; j++)
        {
            _ray.set_from_distance_angle((j - n_s / 2.) * 2 * s_max / (n_s - 1), 2 * M_PI * i / n_theta);
            _ray.offset({size / 2., size / 2.});
            projection.set(i + 1, j + 1, project(my_image, _ray));
        }
    }
    projection.save("projection");

    if (true)
    {
        auto error = system("python ../display_image.py projection.txt");
        if (error)
            std::cout << "Python execution failed" << std::endl;
    }
}