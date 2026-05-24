#pragma once
#include <random>

inline std::mt19937 generator(0);

inline double random_normal(double mean, double var)
{
    return std::normal_distribution<double>(mean, var)(generator);
}

inline double random_poisson(double mean)
{
    return std::poisson_distribution<size_t>(mean)(generator);
}

/// @brief Simulates photon noise in a image.
/// @param scaling How much photon detection events match one intensity unit in the image.
inline void add_photon_noise(image &im, double scaling)
{
    im.apply_elementwise([scaling](double x)
                         { return random_poisson(x * scaling) / scaling; });
}
/// @brief Adds a centered gaussian noise to the background to approximate effects such as read noise
inline void add_background_noise(image &im, double variance)
{
    im.apply_elementwise([variance](double x)
                         { return x + random_normal(0, variance); });
}