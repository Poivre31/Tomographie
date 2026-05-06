#pragma once
#include <vector>
#include <complex>
#include "image.h"
using namespace std::complex_literals;
using complex = std::complex<double>;

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

std::vector<complex> dft(std::vector<double> data)
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

std::vector<complex> dft_2D(image data)
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

std::vector<complex> fft(std::vector<double> data)
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
            result[k] = even[k] + exp(-2 * M_PI * k / N * 1i) * odd[k];
            result[k + N / 2] = even[k] - exp(-2 * M_PI * k / N * 1i) * odd[k];
        }
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
        result[i + N / 2] = abs(data[i]);
    }
    for (size_t i = 0; i < N / 2; i++)
    {
        result[i] = abs(data[i + N / 2]);
    }
    return result;
}

std::vector<double> modulo(std::vector<complex> data)
{
    std::vector<double> result(data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        result[i] = abs(data[i]);
    }
    return result;
}