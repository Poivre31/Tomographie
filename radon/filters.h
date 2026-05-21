#pragma once
#include "image.h"
#include "complex_matrix.h"

double hamming_weight()
{
    return 0.;
}

void weight_data_with_window(complex_matrix &data, double radius)
{
    size_t N = data.width();

    for (size_t i = 1; i <= N; i++)
    {
        for (size_t j = 1; j <= N; j++)
        {
            double d2 = (i - N / 2.) * (i - N / 2.) + (j - N / 2.) * (j - N / 2.);
            double weight = d2 <= radius * radius;
            data.set(i, j, data.get(i, j) * weight);
        }
    }
}