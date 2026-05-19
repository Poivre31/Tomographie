#pragma once
#include <random>

std::mt19937 generator(0);

double random_normal(double mean, double var)
{
    return std::normal_distribution<double>(mean, var)(generator);
}
