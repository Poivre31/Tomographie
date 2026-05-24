#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "image.h"

void save_vector(std::vector<double> data, std::string path);

void display_image(image im, double gamma = 1);

image load_image_png(std::string path);
image load_image_txt(std::string path);

void display_images(std::vector<image> images, double gamma = 1);

void display_images(std::vector<image> images, std::vector<double> gamma);

void display_plot(std::vector<double> data);