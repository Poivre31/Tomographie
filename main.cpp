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
    size_t n = 1024;
    size_t a = 32;

    complex_matrix aperture(n, n);

    for (size_t i = 1; i <= n; i++)
    {
        for (size_t j = 1; j <= n; j++)
        {
            if ((i - n / 2.) * (i - n / 2.) + (j - n / 2.) * (j - n / 2.) < a * a)
                aperture.set(i, j, 1);
            else
                aperture.set(i, j, 0);
        }
    }

    t.start_watch();
    auto im = fft_2D_shift(fft_2D(aperture)).modulus_to_image();
    t.print_ellapsed_time();

    im.apply_elementwise([](double x)
                         { return pow(x, 1. / 2.2); });
    im.save("fft_2D");
    system("python ../display_image.py fft_2D.txt");

    // std::vector<double> aperture(n);
    // for (size_t i = 0; i < n; i++)
    // {
    //     if (abs(i - n / 2.) < a)
    //         aperture[i] = 1;
    //     else
    //         aperture[i] = 0;
    // }
    // t.start_watch();
    // auto datafft = fft_shift(modulus(fft(aperture)));
    // t.print_ellapsed_time();

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

    t.start_watch();
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
    t.print_ellapsed_time();

    projection.save("projection");

    if (true)
    {
        auto error = system("python ../display_image.py projection.txt");
        if (error)
            std::cout << "Python execution failed" << std::endl;
    }
}