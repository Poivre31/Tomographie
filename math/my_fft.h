#pragma once
#include "my_dft.h"
#include "timer.h"

template <typename T>
std::vector<complex> fft(std::vector<T> data, bool recurrence = false)
{
    size_t N = data.size();

    std::vector<complex> result(N);
    if (!(N && (N && (N - 1))))
    {
        std::cout << "FFT implementation only works for data size in powers of 2" << std::endl;
        return result;
    }

    if (!recurrence)
    {
        timer::continue_watch("fft");
        data = fft_shift(data);
    }

    if (N == 1)
        return {data[0]};
    if (N == 2)
        return dft(data);

    else
    {
        auto even = fft(stride(data, 2, 0), true);
        auto odd = fft(stride(data, 2, 1), true);
        for (size_t k = 0; k < N / 2; k++)
        {
            result[k] = even[k] + exp(-2 * M_PI * k / N * 1i) * odd[k];
            result[k + N / 2] = even[k] - exp(-2 * M_PI * k / N * 1i) * odd[k];
        }
    }
    if (!recurrence)
    {
        timer::pause_watch("fft");
        return fft_shift(result);
    }
    else
        return result;
}

template <typename T>
std::vector<complex> ffti(std::vector<T> data, bool recurrence = false)
{
    size_t N = data.size();

    std::vector<complex> result(N);
    if (!(N && (N && (N - 1))))
    {
        std::cout << "FFT implementation only works for data size in powers of 2" << std::endl;
        return result;
    }

    // Ne normalise qu'une seule fois
    if (!recurrence)
    {
        timer::continue_watch("fft");
        for (size_t i = 0; i < N; i++)
        {
            data[i] /= N;
        }
        data = fft_shift(data);
    }

    if (N == 1)
        return data;
    if (N == 2)
        return dfti(data, false);

    else
    {
        auto even = ffti(stride(data, 2, 0), true);
        auto odd = ffti(stride(data, 2, 1), true);
        for (size_t k = 0; k < N / 2; k++)
        {
            result[k] = (even[k] + exp(2 * M_PI * k / N * 1i) * odd[k]);
            result[k + N / 2] = (even[k] - exp(2 * M_PI * k / N * 1i) * odd[k]);
        }
    }

    if (!recurrence)
    {
        timer::pause_watch("fft");
        return fft_shift(result);
    }
    else
        return result;
}

complex_matrix fft_2D(complex_matrix data, bool recurrence = false)
{
    size_t N = data.width();
    size_t M = data.height();
    complex_matrix result(N, M);

    if (!(N && (N && (N - 1))) || N != M)
    {
        std::cout << "FFT implementation only works for squares of size in powers of 2" << std::endl;
        return result;
    }

    if (!recurrence)
    {
        timer::continue_watch("fft");
        data = fft_2D_shift(data);
    }

    for (size_t k = 1; k <= N; k++)
    {
        result.set_column(fft(data.get_column(k), true), k);
    }
    for (size_t l = 1; l <= M; l++)
    {
        result.set_line(fft(result.get_line(l), true), l);
    }

    if (!recurrence)
    {
        timer::pause_watch("fft");
        return fft_2D_shift(result);
    }
    else
        return result;
}

complex_matrix ffti_2D(complex_matrix data, bool recurrence = false)
{
    size_t N = data.width();
    size_t M = data.height();
    complex_matrix result(N, M);

    if (!(N && (N && (N - 1))) || N != M)
    {
        std::cout << "FFT implementation only works for squares of size in powers of 2" << std::endl;
        return result;
    }

    if (!recurrence)
    {
        timer::continue_watch("fft");
        data = fft_2D_shift(data);
        data.apply_elementwise([N](complex z)
                               { return 1. / (N * N) * z; });
    }

    for (size_t k = 1; k <= N; k++)
    {
        result.set_column(ffti(data.get_column(k), true), k);
    }
    for (size_t l = 1; l <= M; l++)
    {
        result.set_line(ffti(result.get_line(l), true), l);
    }

    if (!recurrence)
    {
        timer::pause_watch("fft");
        return fft_2D_shift(result);
    }
    else
        return result;
}
