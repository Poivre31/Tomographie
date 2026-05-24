#include "ssim.h"

double mean(image im)
{
    double sum = 0;
    im.apply_elementwise([&sum](size_t i, size_t j, double v)
                         {sum+=v;return v; });
    return sum / (im.width() * im.height());
}

double weighted_mean(image im, image weight)
{
    if (im.width() != weight.width() || im.height() != weight.height())
    {
        std::cout << "ERROR: image dimensions must watch (computing psnr)" << std::endl;
        return 0.;
    }
    double sum = 0;
    im.apply_elementwise([&sum, weight](size_t i, size_t j, double v)
                         {sum+=weight.get(i,j)*v;return v; });
    return sum;
}

double variance(image im)
{
    double avg = mean(im);
    double variance = 0;
    im.apply_elementwise([&variance, avg](size_t i, size_t j, double v)
                         {variance+=(v-avg)*(v-avg); return v; });

    return variance;
}

double weighted_variance(image im, image weight)
{
    if (im.width() != weight.width() || im.height() != weight.height())
    {
        std::cout << "ERROR: image dimensions must watch (computing psnr)" << std::endl;
        return 0.;
    }
    double mean = weighted_mean(im, weight);
    double variance = 0;
    im.apply_elementwise([&variance, mean, weight](size_t i, size_t j, double v)
                         {variance+=weight.get(i,j)*(v-mean)*(v-mean); return v; });

    return variance;
}

image normalize(image im)
{
    image result = im.copy();
    double avg = mean(im);
    double var = variance(im);
    if (var == 0)
    {
        result.fill_uniform(1.);
        return result;
    }
    result.apply_elementwise([avg, var](double v)
                             { return (v - avg) / sqrt(var); });
    return result;
}

double sample_covariance(image im1, image im2, image weight)
{
    if (im1.width() != im2.width() || im1.height() != im2.height() || im1.width() != weight.width() || im1.height() != weight.height())
    {
        std::cout << "ERROR: image dimensions must watch (computing psnr)" << std::endl;
        return 0.;
    }
    double mean_1 = weighted_mean(im1, weight);
    double mean_2 = weighted_mean(im2, weight);
    double covariance = 0;
    for (size_t i = 1; i <= im1.width(); i++)
    {
        for (size_t j = 1; j <= im1.height(); j++)
        {
            covariance += weight.get(i, j) * (im1.get(i, j) - mean_1) * (im2.get(i, j) - mean_2);
        }
    }
    return covariance;
}

double ssim(image im1, image im2, image weight_kernel)
{
    if (im1.width() != im2.width() || im1.height() != im2.height())
    {
        std::cout << "ERROR: image dimensions must watch (computing psnr)" << std::endl;
        return 0.;
    }
    double k1 = 0.01;
    double k2 = 0.03;
    double L = 1;
    double c1 = k1 * k1 * L * L;
    double c2 = k2 * k2 * L * L;

    double mean_1 = weighted_mean(im1, weight_kernel);
    double mean_2 = weighted_mean(im2, weight_kernel);
    double variance_1 = weighted_variance(im1, weight_kernel);
    double variance_2 = weighted_variance(im2, weight_kernel);
    double covariance = sample_covariance(im1, im2, weight_kernel);

    return (2 * mean_1 * mean_2 + c1) * (2 * covariance + c2) / (mean_1 * mean_1 + mean_2 * mean_2 + c1) / (variance_1 + variance_2 + c2);
}

image gaussian_kernel(size_t size, double stdev)
{
    image kernel(size, size);
    if (size % 2 == 0)
    {
        std::cout << "Gaussian kernel size must be odd" << std::endl;
        return kernel;
    }
    size_t mu = size / 2 + 1;
    double sum = 0;
    for (size_t i = 1; i <= size; i++)
    {
        for (size_t j = 1; j <= size; j++)
        {
            double weight = exp(-1 / (2. * stdev * stdev) * ((i - mu) * (i - mu) + (j - mu) * (j - mu)));
            kernel.set(i, j, weight);
            sum += weight;
        }
    }
    kernel.apply_elementwise([sum](double v)
                             { return v / sum; });
    return kernel;
}

double mssim(image im1, image im2, bool log_scale, size_t window_width, double stdev)
{
    im1 = normalize(im1);
    im2 = normalize(im2);
    auto kernel = gaussian_kernel(window_width, stdev);
    if (im1.width() != im2.width() || im1.height() != im2.height())
    {
        std::cout << "ERROR: image dimensions must watch (computing psnr)" << std::endl;
        return 0.;
    }
    double mssim = 0.;
    size_t N = 0;
    for (size_t i = 1; i <= im1.width() - window_width + 1; i++)
    {
        for (size_t j = 1; j <= im1.height() - window_width + 1; j++)
        {
            auto win_1 = im1.get_portion(i, j, i + window_width, j + window_width);
            auto win_2 = im2.get_portion(i, j, i + window_width, j + window_width);

            mssim += ssim(win_1, win_2, kernel);
            N++;
        }
    }
    mssim /= N;
    if (log_scale)
        return -10 * log10(1 - mssim);
    else
        return mssim;
}