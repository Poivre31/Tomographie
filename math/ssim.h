#pragma once
#include "image.h"
#include <cmath>

double mean(image im);

double weighted_mean(image im, image weight);

double variance(image im);

double weighted_variance(image im, image weight);

image normalize(image im);

double sample_covariance(image im1, image im2, image weight);

double ssim(image im1, image im2, image weight_kernel);

image gaussian_kernel(size_t size, double stdev);

double mssim(image im1, image im2, bool log_scale = true, size_t window_width = 11, double stdev = 1.5);