#pragma once
#include "image.h"
#include "complex_matrix.h"

complex_matrix weight_data_ram_lak(complex_matrix data, double radius);

complex_matrix weight_data_shepp_logan(complex_matrix data, double radius);

complex_matrix weight_data_hanning(complex_matrix data, double radius);

image correct_sinc(image im);