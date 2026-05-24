#pragma once
#include "ray.h"
#include "timer.h"

std::vector<double> grid_intersects(size_t width, size_t height, ray r);

double project(image &im, ray r);