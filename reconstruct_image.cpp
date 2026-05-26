#include "data/image.h"
#include "timer.h"
#include "radon/sinogram.h"
#include "exemples.h"
#include "my_random.h"
#include "filters.h"
#include "bilinear_interp.h"
#include "psnr.h"
#include <format>
#include "ssim.h"
#include "config.h"

int main()
{
    timer::start_watch();

    std::cout << "### Reconstructing image ###" << std::endl;
    std::cout << "Loading data" << std::endl;
    auto phantom = load_image_txt("phantom.txt");
    auto phantom_fft = fft_2D(phantom);
    auto projection = load_image_txt("sinogram.txt");

    size_t n_image = phantom.width();
    size_t n_sensor = projection.width();
    size_t n_projections = projection.height();

    complex_matrix fft_1(n_sensor, n_projections);
    for (size_t s = 1; s <= n_projections; s++)
    {
        std::cout << "\r\33[KComputing fourier slices (" << round(100. * s / (n_projections - 1)) << "%)" << std::flush;
        fft_1.set_line(fft(projection.get_line(s)), s);
    }
    std::cout << std::endl;

    complex_matrix polar(n_sensor, n_sensor);
    image weight(n_sensor, n_sensor);

    for (size_t t = 0; t < n_projections; t++)
    {
        auto v = fft_1.get_line(t + 1);
        double theta = 2 * M_PI * t / n_projections;
        std::cout << "\r\33[KInterpolating polar slices onto cardesian grid (" << round(100. * t / (n_projections - 1)) << "%)" << std::flush;
        for (size_t i = 0; i < n_sensor; i++)
        {
            double d = (i - n_sensor / 2.);

            double x = n_sensor / 2. + cos(theta) * d + 1;
            double y = n_sensor / 2. + sin(theta) * d + 1;

            auto [x1, x2, y1, y2, w11, w12, w21, w22] = bilinear_weights(phantom, x, y);
            // polar.set(floor(x) - 1, floor(y) - 1, x - 1);

            polar.increment(x1, y1, v[i] * w11);
            weight.increment(x1, y1, w11);
            polar.increment(x1, y2, v[i] * w12);
            weight.increment(x1, y2, w12);
            polar.increment(x2, y1, v[i] * w21);
            weight.increment(x2, y1, w21);
            polar.increment(x2, y2, v[i] * w22);
            weight.increment(x2, y2, w22);

            // polar.increment(floor(x), floor(y), v[i]);
            // weight.increment(floor(x), floor(y), 1);
        }
    }
    std::cout << std::endl;

    for (size_t i = 1; i <= n_sensor; i++)
    {
        for (size_t j = 1; j <= n_sensor; j++)
        {
            if (weight.get(i, j) != 0)
                polar.set(i, j, polar.get(i, j) / weight.get(i, j));
        }
    }

    std::cout << "Filtering frequencies and computing inverse fourier transform" << std::endl;

    double dn = n_sensor / 2.;
    auto polar_ram_lak = weight_data_ram_lak(polar, dn);
    auto polar_shepp_logan = weight_data_shepp_logan(polar, dn);
    auto polar_hanning = weight_data_hanning(polar, dn);

    auto result_raw = ffti_2D(polar).modulus_to_image();
    auto result_ram_lak = ffti_2D(polar_ram_lak).modulus_to_image();
    auto result_shepp_logan = ffti_2D(polar_shepp_logan).modulus_to_image();
    auto result_hanning = ffti_2D(polar_hanning).modulus_to_image();

    // std::cout << "Reconstruction quality (log scale SSIM): \n  Raw: " << mssim(result_raw, phantom) << "dB\n"
    //           << "  Ram Lak: " << mssim(result_ram_lak, phantom) << "dB\n"
    //           << "  Shepp Logan: " << mssim(result_shepp_logan, phantom) << "dB\n"
    //           << "  Hanning: " << mssim(result_hanning, phantom) << "dB\n";

    std::cout << "### Reconstructed image in " << timer::get_ellapsed_time() << "ms ###\n"
              << std::endl;

    display_images({
                       phantom_fft.modulus_to_image(),
                       polar.modulus_to_image(),
                       polar_shepp_logan.modulus_to_image(),
                       polar_hanning.modulus_to_image(),
                   },
                   {
                       "'Spectrum of reference image'",
                       "'Spectrum of reconstructed image'",
                       "'Spectrum of Shepp-Logan filtered image'"
                       "'Spectrum of Hann filtered image'",
                   },
                   4);
    display_images({
                       phantom,
                       result_raw,
                       result_shepp_logan,
                       result_hanning,
                   },
                   {
                       "'Reference image'",
                       "'Reconstructed image'",
                       "'Shepp-Logan filtered image'"
                       "'Hann filtered image'",
                   },
                   1.);

    std::cout << "Time spent doing FFT " << timer::get_ellapsed_time("fft") << "ms" << std::endl;
}