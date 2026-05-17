#include "data/image.h"
#include "timer.h"
#include "radon/sinogram.h"
#include "exemples.h"

double overlap_circles(vec2 c1, vec2 c2, double radius = sqrt(2))
{
    double d = (c1 - c2).norm();
    if (d >= 2 * radius)
        return 0;
    if (d <= radius)
        return M_PI * radius * radius;
    else
    {
        return 2 * radius * radius * asin(sqrt(1 - d * d / (4 * radius * radius))) - radius * sqrt(4 * radius * radius - d * d);
    }
}

int main()
{
    timer::start_watch();
    size_t size = 256;
    double d_max = size / 2;
    image phantom(size, size);

    // phantom.fill_ellipse(1., size / 2, size / 2, size / 16, size / 16);
    // phantom.fill_rectangle(1, size / 2, size / 2, size / 4, size / 8);
    phantom.fill_phantom(size / 2, size / 2, .5 * size);
    auto phantom_fft = fft_2D(phantom);

    timer::start_watch("sinogram");
    auto projection = sinogram(phantom, size, size, d_max);
    timer::print_ellapsed_time("sinogram");

    complex_matrix fft_1(size, size);
    for (size_t s = 1; s <= size; s++)
    {
        fft_1.set_line(fft(projection.get_line(s)), s);
    }
    complex_matrix polar(size, size);
    image weight(size, size);

    for (size_t t = 0; t < size; t++)
    {
        auto v = fft_1.get_line(t + 1);
        double theta = 2 * M_PI * t / size;
        for (size_t i = 0; i < size; i++)
        {
            double d = (2. * i - size) * d_max / (size - 1);

            double x = size / 2. + cos(theta) * d;
            double y = size / 2. + sin(theta) * d;

            polar.increment(round(x), round(y), v[i]);
            weight.increment(round(x), round(y), 1);
        }
    }

    // timer::start_watch();
    // for (size_t i = 1; i <= size; i++)
    // {
    //     for (size_t j = 1; j <= size; j++)
    //     {
    //         for (size_t t = 0; t < size; t++)
    //         {
    //             auto v = fft_1.get_line(t + 1);
    //             double theta = 2 * M_PI * t / size;
    //             for (size_t s = 0; s < size; s++)
    //             {
    //                 double d = (2. * s - size) * d_max / (size - 1);

    //                 double x = size / 2. + cos(theta) * d;
    //                 double y = size / 2. + sin(theta) * d;
    //                 double c = overlap_circles({x, y}, {(double)i, (double)j});
    //                 polar.increment(i, j, c * v[s]);
    //                 weight.increment(i, j, c);
    //             }
    //         }
    //     }
    // }
    // timer::print_ellapsed_time();

    for (size_t i = 1; i <= size; i++)
    {
        for (size_t j = 1; j <= size; j++)
        {
            if (weight.get(i, j) != 0)
                polar.set(i, j, polar.get(i, j) / weight.get(i, j));
        }
    }
    timer::print_ellapsed_time("project");
    timer::print_ellapsed_time("fft");
    timer::print_ellapsed_time();
    return 0;
    display_images({fft_1.modulus_to_image(),
                    phantom_fft.modulus_to_image(),
                    polar.modulus_to_image(),
                    fft_1.phase_to_image(),
                    phantom_fft.phase_to_image(),
                    polar.phase_to_image()},
                   {3., 3., 3., 1., 1., 1.});

    // display_image(phantom_fft.phase_to_image(), 1);
    // display_image(polar.phase_to_image(), 1);
    // display_image(phantom);
    // // display_image(projection);
    display_images({phantom, projection, ffti_2D(polar).modulus_to_image()});
}