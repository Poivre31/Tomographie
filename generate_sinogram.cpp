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
#include <filesystem>
#include "config.h"

int main()
{
    timer::start_watch();
    config cfg = get_config();
    std::cout << "### Generating sinogram ###" << std::endl;
    size_t n_image = cfg.n_image;

    image phantom(n_image, n_image);

    if (std::filesystem::exists(std::string("../resources/") + cfg.image_name))
    {
        std::cout << "Loading image file" << std::endl;
        phantom = load_image_png(cfg.image_name);
        n_image = phantom.width();
    }

    else
    {
        std::string shape = cfg.image_name;
        std::cout << "Generating image shape '" << shape << "'" << std::endl;

        if (shape == "shepp-logan")
            phantom.fill_phantom(n_image / 2, n_image / 2, .5 * n_image, true);
        else if (shape == "ellipse")
            phantom.fill_ellipse(1., n_image / 2 + 1, n_image / 2 + 1, n_image / 4, n_image / 4);
        else if (shape == "rectangle")
            phantom.fill_rectangle(1, n_image / 2, n_image / 2, n_image / 4, n_image / 2);
    }
    std::cout << "Computing image's sinogram:" << std::endl;

    double image_scale = cfg.image_size / n_image;        // mm per pixel
    double sensor_scale = cfg.sensor_size / cfg.n_sensor; // mm per pixel
    auto projection = sinogram(phantom, image_scale, cfg.n_projections, cfg.n_sensor, sensor_scale);

    phantom.save("phantom");
    projection.save("sinogram");
    std::cout << "Time projecting: " << timer::get_ellapsed_time("project") << "ms\n";

    std::cout << "### Computed sinogram in " << timer::get_ellapsed_time() << "ms ###\n"
              << std::endl;

    display_images({phantom, projection}, {"'Reference image'", "'Computed sinogram'"});
}