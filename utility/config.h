#pragma once
#include <tuple>
#include <string>
#include <cmath>
#include <fstream>

struct config
{
    std::string image_name;
    double image_size;
    size_t n_image;
    double sensor_size;
    size_t n_sensor;
    size_t n_projections;
};

inline config get_config()
{
    config cfg;
    std::ifstream data("../run/config.txt");
    data >> cfg.image_name;
    data >> cfg.image_size;
    data >> cfg.n_image;
    data >> cfg.sensor_size;
    data >> cfg.n_sensor;
    data >> cfg.n_projections;
    return cfg;
}