#pragma once
#include "utility.h"
#include "my_fft.h"
#include "my_math.h"

void exemple_fft_1D(size_t n, size_t a)
{
    std::vector<double> aperture(n);
    for (size_t i = 0; i < n; i++)
    {
        if (abs(i - n / 2.) < a)
            aperture[i] = 1;
        else
            aperture[i] = 0;
    }
    timer::start_watch();
    auto datafft = fft_shift(modulus(fft(aperture)));
    timer::print_ellapsed_time();

    display_plot(aperture);
    display_plot(datafft);
}

void exemple_fft_2D(size_t n, size_t a)
{
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

    timer::start_watch();
    auto im = fft_2D_shift(fft_2D(aperture)).modulus_to_image();
    timer::print_ellapsed_time();

    im.apply_elementwise([](double x)
                         { return pow(x, 1. / 2.2); });
    display_image(im);
}