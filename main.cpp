#include "data/image.h"
#include "utility.h"
#include "radon/sinogram.h"
#include "exemples.h"

int main()
{

    // exemple_fft_1D(1024, 30);
    // exemple_fft_2D(1024, 16);

    size_t size = 512;
    image phantom(size, size);

    // phantom.fill_rectangle(1. / (.8 * size), size / 2, size / 2, .8 * size, .8 * size);
    phantom.fill_rectangle(1, size / 2, size / 2, size / 4, size / 4);
    // phantom.fill_phantom(size / 2, size / 2, .8 * size);

    display_image(phantom);

    timer::start_watch();
    auto projection = sinogram(phantom, size, size, size / 2);
    timer::print_ellapsed_time();

    complex_matrix fft_1(size, size);
    for (size_t s = 1; s <= size; s++)
    {
        fft_1.set_line(fft_shift(fft(projection.get_line(s))), s);
    }
    complex_matrix polar(size, size);
    for (size_t t = 1; t <= size; t++)
    {
        auto v = fft_1.get_line(t);
        double theta = 2 * M_PI * t / (size - 1);
        for (size_t i = 1; i <= size; i++)
        {
            double x = size / 2 + (i - size / 2) * cos(theta);
            double y = size / 2 + (i - size / 2) * sin(theta);
            polar.set(round(x), round(y), v[i]);
        }
    }

    display_image(fft_2D_shift(fft_2D(polar)).modulus_to_image());

    if (false)
    {
        display_image(phantom);
        display_image(projection);
    }
}