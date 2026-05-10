#pragma once
#include <complex>
#include <vector>

using namespace std::complex_literals;
using complex = std::complex<double>;

inline std::vector<double> modulus(std::vector<complex> data)
{
    std::vector<double> result(data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        result[i] = abs(data[i]);
    }
    return result;
}

inline std::vector<double> phase(std::vector<complex> data)
{
    std::vector<double> result(data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        result[i] = std::arg(data[i]);
    }
    return result;
}

inline std::vector<double> real(std::vector<complex> data)
{
    std::vector<double> result(data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        result[i] = data[i].real();
    }
    return result;
}

inline std::vector<double> imag(std::vector<complex> data)
{
    std::vector<double> result(data.size());
    for (size_t i = 0; i < data.size(); i++)
    {
        result[i] = data[i].imag();
    }
    return result;
}