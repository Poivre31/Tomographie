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