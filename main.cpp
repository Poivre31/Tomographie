#include "data/image.h"
#include "utility.h"
#include "radon/sinogram.h"
#include "exemples.h"

int main()
{

    // exemple_fft_1D(1024, 30);
    // exemple_fft_2D(1024, 16);

    size_t size = 256;
    image phantom(size, size);

    // phantom.fill_ellipse(1., size / 2, size / 2, size / 16, size / 16);
    // phantom.fill_rectangle(1, size / 2, size / 2, size / 16, size / 16);
    phantom.fill_phantom(size / 2, size / 2, .8 * size);
    auto phantom_fft = fft_2D_shift(fft_2D(phantom));

    timer::start_watch();
    auto projection = sinogram(phantom, size, size, size / 2);
    timer::print_ellapsed_time();

    complex_matrix fft_1(size, size);
    for (size_t s = 1; s <= size; s++)
    {
        fft_1.set_line(fft_shift(fft(projection.get_line(s))), s);
    }
    complex_matrix polar(size, size);
    image weight(size, size);
    for (size_t t = 1; t <= size; t++)
    {
        auto v = fft_1.get_line(t);
        double theta = 2 * M_PI * t / (size - 1);
        for (size_t i = 1; i <= size; i++)
        {
            double x = size / 2. + cos(theta) * (i - size / 2.);
            double y = size / 2. + sin(theta) * (i - size / 2.);
            double phase = std::arg(phantom_fft.get(ceil(x), ceil(y)));
            complex z = abs(v[i]) * exp(1i * phase);
            if (abs(z) > 0)
            {
                polar.increment(ceil(x), ceil(y), v[i]);
                weight.increment(ceil(x), ceil(y), 1);
            }
            // if (abs(i - size / 2) > size / 8)
            //     polar.set(ceil(x), ceil(y), 0);
        }
    }

    for (size_t i = 1; i <= size; i++)
    {
        for (size_t j = 1; j <= size; j++)
        {
            if (weight.get(i, j) != 0)
                polar.set(i, j, polar.get(i, j) / weight.get(i, j));
        }
    }

    polar.rotate(1, 1);

    display_images({phantom_fft.phase_to_image(), polar.phase_to_image(), projection}, 3);
    display_images({phantom_fft.phase_to_image(), polar.phase_to_image(), phantom, projection}, 1);
    display_images({phantom_fft.modulus_to_image(), polar.modulus_to_image(), phantom, projection}, {4., 2., 1., 1.});

    // display_image(phantom_fft.phase_to_image(), 1);
    // display_image(polar.phase_to_image(), 1);
    // display_image(phantom);
    // // display_image(projection);
    // display_image(ffti_2D(polar).modulus_to_image());

    if (false)
    {
        display_image(phantom);
        display_image(projection);
    }
}