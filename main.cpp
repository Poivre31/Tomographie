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

double image_size = 600;         // Physical size of the image in mm
size_t n_image = 512;            // Number of pixels of the representation of the image used to compute the projection
size_t n_sensor = 512;           // Number of pixels in the physical sensor
double sensor_size = image_size; // Physical size of the sensor
size_t n_projections = 1024;     // Number of projections
double theta0 = 0;

int main()
{
    timer::start_watch();
    double image_scale = image_size / n_image;    // mm per pixel
    double sensor_scale = sensor_size / n_sensor; // mm per pixel
    image phantom(n_image, n_image);

    // phantom.fill_ellipse(1., n_image / 2 + 1, n_image / 2 + 1, n_image / 2, n_image / 2);
    // phantom.fill_rectangle(1, n_image / 2, n_image / 2, 1. * n_image, 1. * n_image);
    phantom.fill_phantom(n_image / 2, n_image / 2, .5 * n_image, true);
    auto phantom_fft = fft_2D(phantom);

    auto projection = sinogram(phantom, image_scale, n_projections, n_sensor, sensor_scale, theta0);
    // display_image(projection);
    // add_photon_noise(projection, 10);

    complex_matrix fft_1(n_sensor, n_projections);
    for (size_t s = 1; s <= n_projections; s++)
    {
        fft_1.set_line(fft(projection.get_line(s)), s);
    }

    complex_matrix polar(n_image, n_image);
    image weight(n_image, n_image);

    for (size_t t = 0; t < n_projections; t++)
    {
        auto v = fft_1.get_line(t + 1);
        double theta = 2 * M_PI * t / n_projections + theta0;
        for (size_t i = 0; i < n_sensor; i++)
        {
            double d = (i - n_sensor / 2.);

            double x = n_image / 2. + cos(theta) * d + 1;
            double y = n_image / 2. + sin(theta) * d + 1;

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

    for (size_t i = 1; i <= n_image; i++)
    {
        for (size_t j = 1; j <= n_image; j++)
        {
            if (weight.get(i, j) != 0)
                polar.set(i, j, polar.get(i, j) / weight.get(i, j));
        }
    }

    // double dn = std::min(n_sensor / 2., n_sensor * sensor_scale * n_projections / (2 * M_PI * image_size));
    double dn = n_sensor / 2.;
    auto result_raw = ffti_2D(polar).modulus_to_image();
    auto result_ram_lak = ffti_2D(weight_data_ram_lak(polar, dn)).modulus_to_image();
    auto result_shepp_logan = ffti_2D(weight_data_shepp_logan(polar, dn)).modulus_to_image();
    auto result_hanning = ffti_2D(weight_data_hanning(polar, dn)).modulus_to_image();

    std::cout << "Reconstruction quality (log scale SSIM): \n  Raw: " << mssim(result_raw, phantom, true, 21) << "dB\n"
              << "  Ram Lak: " << mssim(result_ram_lak, phantom, true, 21) << "dB\n"
              << "  Shepp Logan: " << mssim(result_shepp_logan, phantom, true, 21) << "dB\n"
              << "  Hanning: " << mssim(result_hanning, phantom, true, 21) << "dB\n";

    timer::print_ellapsed_time("project");
    timer::print_ellapsed_time();

    display_images({
                       fft_1.modulus_to_image(),
                       phantom_fft.modulus_to_image(),
                       polar.modulus_to_image(),
                       weight_data_ram_lak(polar, dn).modulus_to_image(),
                       weight_data_shepp_logan(polar, dn).modulus_to_image(),
                       weight_data_hanning(polar, dn).modulus_to_image(),
                   },
                   3);
    display_images({
                       phantom,
                       result_raw,
                       result_ram_lak,
                       result_shepp_logan,
                       result_hanning,
                   },
                   1.);
    timer::print_ellapsed_time("fft");
}