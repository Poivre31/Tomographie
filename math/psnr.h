#pragma once
#include "image.h"
#include <cmath>
#include "ssim.h"

double psnr(image im1, image im2, double max_i)
{
    if (im1.width() != im2.width() || im1.height() != im2.height())
    {
        std::cout << "ERROR: image dimensions must watch (computing psnr)" << std::endl;
        return 0.;
    }

    double mse = 0;
    for (size_t i = 1; i <= im1.width(); i++)
    {
        for (size_t j = 1; j <= im1.height(); j++)
        {
            mse += (im1.get(i, j) - im2.get(i, j)) * (im1.get(i, j) - im2.get(i, j));
        }
    }
    mse /= im1.width() * im1.height();
    return 10 * log10(max_i * max_i / mse);
}