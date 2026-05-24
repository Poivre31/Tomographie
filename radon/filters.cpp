#include "filters.h"

complex_matrix weight_data_ram_lak(complex_matrix data, double radius)
{
    size_t N = data.width();
    complex_matrix result = data.copy();

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            double d = sqrt((i - N / 2.) * (i - N / 2.) + (j - N / 2.) * (j - N / 2.));
            double weight = d <= radius;
            result.set(i, j, data.get(i, j) * weight);
        }
    }
    return result;
}

complex_matrix weight_data_shepp_logan(complex_matrix data, double radius)
{
    size_t N = data.width();
    complex_matrix result = data.copy();

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            double d = sqrt((i - N / 2.) * (i - N / 2.) + (j - N / 2.) * (j - N / 2.));
            double x = M_PI * d / (2 * radius);
            double weight = d > radius ? 0 : (x == 0 ? 1 : sin(x) / x);
            result.set(i, j, data.get(i, j) * weight);
        }
    }
    return result;
}

complex_matrix weight_data_hanning(complex_matrix data, double radius)
{
    size_t N = data.width();
    complex_matrix result = data.copy();

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            double d = sqrt((i - N / 2.) * (i - N / 2.) + (j - N / 2.) * (j - N / 2.));
            double weight = d > radius ? 0 : .5 * (1 + cos(M_PI * d / radius));
            result.set(i, j, data.get(i, j) * weight);
        }
    }
    return result;
}

image correct_sinc(image im)
{
    image result = im.copy();
    size_t N = im.width();
    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            double d = sqrt((i - N / 2.) * (i - N / 2.) + (j - N / 2.) * (j - N / 2.));
            double x = 2 * M_PI * d / N;
            double weight = d >= .75 * N / 2 ? 0 : (x == 0 ? 1 : x / sin(x));
            result.set(i, j, im.get(i, j) * weight / 1.17898);
        }
    }
    return result;
}