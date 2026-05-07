#pragma once
#include <vector>
#include "my_math.h"
#include "complex.h"
#include "complex_matrix.h"

template <typename T>
std::vector<T> stride(std::vector<T> data, size_t step, size_t offset)
{
    std::vector<T> out;
    for (size_t i = offset; i < data.size(); i += step)
    {
        out.push_back(data[i]);
    }
    return out;
}

template <typename T>
std::vector<complex> dft(std::vector<T> data)
{
    size_t N = data.size();
    std::vector<complex> result(N);
    for (size_t k = 0; k < N; k++)
    {
        for (size_t n = 0; n < N; n++)
        {
            result[k] += data[n] * exp(-2 * M_PI * n * k / N * 1i);
        }
    }

    return result;
}

// complex_matrix dft_2D(complex_matrix data)
// {
//     size_t N = data.width();
//     size_t M = data.height();
//     complex_matrix result(N, M);
//     for (size_t k = 1; k <= N; k++)
//     {
//         for (size_t l = 1; l <= M; l++)
//         {
//             complex value = 0;
//             for (size_t n = 1; n <= N; n++)
//             {
//                 for (size_t m = 1; m <= M; m++)
//                 {
//                     value += data.get(m, n) * exp(-2 * (M_PI * (k - 1) * (m - 1) / M + M_PI * (l - 1) * (n - 1) / N) * 1i);
//                 }
//             }
//             result.set(k, l, value);
//         }
//     }

//     return result;
// }

template <typename T>
std::vector<complex> fft(std::vector<T> data)
{
    size_t N = data.size();
    std::vector<complex> result(N);
    if (!(N && (N && (N - 1))))
    {
        std::cout << "FFT implementation only works for data size in powers of 2" << std::endl;
        return result;
    }

    if (N == 2)
    {
        return dft(data);
    }

    else
    {
        auto even = fft(stride(data, 2, 0));
        auto odd = fft(stride(data, 2, 1));
        for (size_t k = 0; k < N / 2; k++)
        {
            result[k] = 1. / N * (even[k] + exp(-2 * M_PI * k / N * 1i) * odd[k]);
            result[k + N / 2] = 1. / N * (even[k] - exp(-2 * M_PI * k / N * 1i) * odd[k]);
        }
    }

    return result;
}

complex_matrix fft_2D(complex_matrix data)
{
    size_t N = data.width();
    size_t M = data.height();
    complex_matrix result(N, M);

    if (!(N && (N && (N - 1))) || N != M)
    {
        std::cout << "FFT implementation only works for squares of size in powers of 2" << std::endl;
        return result;
    }

    for (size_t k = 1; k <= N; k++)
    {
        result.set_column(fft(data.get_column(k)), k);
    }
    for (size_t l = 1; l <= M; l++)
    {
        result.set_line(fft(result.get_line(l)), l);
    }

    return result;
}

template <typename T>
std::vector<T> fft_shift(std::vector<T> data)
{
    size_t N = data.size();
    std::vector<T> result(N);
    for (size_t i = 0; i < N / 2; i++)
    {
        result[i + N / 2] = data[i];
    }
    for (size_t i = 0; i < N / 2; i++)
    {
        result[i] = data[i + N / 2];
    }
    return result;
}

complex_matrix fft_2D_shift(complex_matrix data)
{
    size_t N = data.width();
    size_t M = data.height();
    complex_matrix result(N, M);

    for (size_t k = 1; k <= N / 2; k++)
    {
        for (size_t l = 1; l <= M / 2; l++)
        {
            result.set(k + N / 2, l, data.get(k, l + M / 2));
        }
        for (size_t l = 1; l <= M / 2; l++)
        {
            result.set(k + N / 2, l + M / 2, data.get(k, l));
        }
    }
    for (size_t k = 1; k <= N / 2; k++)
    {
        for (size_t l = 1; l <= M / 2; l++)
        {
            result.set(k, l, data.get(k + N / 2, l + M / 2));
        }
        for (size_t l = 1; l <= M / 2; l++)
        {
            result.set(k, l + M / 2, data.get(k + N / 2, l));
        }
    }

    return result;
}