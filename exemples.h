#pragma once
#include "timer.h"
#include "save.h"
#include "my_fft.h"
#include "my_math.h"
#include "projection.h"

void exemple_fft_1D(size_t n, size_t a)
{
    timer::start_watch("exemple");
    std::vector<double> aperture(n);
    for (size_t i = 0; i < n; i++)
    {
        if (std::abs(i - n / 2.) < a)
            aperture[i] = 1;
        else
            aperture[i] = 0;
    }
    auto datafft = fft(aperture);
    auto ifft = ffti(datafft);

    timer::print_ellapsed_time("exemple");
    // display_plot(aperture);
    display_plot(real(datafft));
    display_plot(real(ifft));
}

void exemple_fft_2D(size_t n, size_t a)
{
    timer::start_watch("exemple");
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

    auto im = fft_2D(aperture);
    auto ifft = ffti_2D(im).real_part_to_image();

    timer::print_ellapsed_time("exemple");
    display_images({im.real_part_to_image(), ifft}, 2.2);
}

void visualize_intersections(size_t width, size_t height)
{
    size_t n = 6;
    ray r;
    std::vector<vec2> positions;
    for (size_t k = 0; k < n; k++)
    {
        r.set_from_distance_angle(0, 2 * M_PI * k / n);
        r.offset({width / 2., height / 2.});
        auto newpos = grid_intersects(width, height, r);
        positions.insert(positions.end(), newpos.begin(), newpos.end());
    }

    std::ofstream file("data.txt");
    file << positions.size() << "\n";
    for (auto xy : positions)
    {
        file << xy.x << "\n";
        file << xy.y << "\n";
    }
    file.close();
    auto error = system("python ../display_scatter.py");
}