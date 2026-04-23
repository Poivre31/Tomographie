#include "image.h"

image::image(size_t width, size_t height) : _width(width), _height(height)
{
    if (width <= 0 || height <= 0)
    {
        std::cout << "Error: invalid image size" << std::endl;
        return;
    }

    _data = new double[width * height];
    if (!_data)
    {
        std::cout << "Image allocation failed" << std::endl;
    }
}

image::~image()
{
    delete[] _data;
}

size_t image::width()
{
    return _width;
}

size_t image::height()
{
    return _height;
}

/// @brief Returns the pixel value at (`x`,`y`)
/// @param x horizontal position, from one to width / left to right
/// @param y vertical position, from one to height / top to bottom
/// @return
double image::get(size_t x, size_t y)
{
    if (x < 1 || x > _width || y < 1 || y > _width)
    {
        std::cout << "Error: invalid image position" << std::endl;
        return -1.;
    }
    return _data[(x - 1) + _width * (y - 1)];
}

/// @brief Sets the pixel value at (`x`,`y`) to `value`
/// @param x horizontal position, from one to width / left to right
/// @param y vertical position, from one to height / top to bottom
/// @return
void image::set(size_t x, size_t y, double value)
{
    if (x < 1 || x > _width || y < 1 || y > _height)
    {
        std::cout << "Error: invalid image position" << std::endl;
        return;
    }
    _data[(x - 1) + _width * (y - 1)] = value;
}

/// @brief Saves the image to `path`
/// @param path without the extension
void image::save(std::string path)
{
    if (!_data)
    {
        std::cout << "No image data to save" << std::endl;
        return;
    }
    std::ofstream file(path + ".txt");

    file << _width << "\n";
    file << _height << "\n";

    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            file << get(x, y) << "\n";
        }
    }

    file.close();
}

void image::fill_rectangle(double value, size_t x0, size_t y0, size_t width, size_t height, bool add)
{
    size_t x1 = x0 - width / 2;
    size_t x2 = x0 + width / 2;
    size_t y1 = y0 - height / 2;
    size_t y2 = y0 + height / 2;
    for (size_t x = std::max(x1, (size_t)0); x < std::min(x2, _width); x++)
    {
        for (size_t y = std::max(y1, (size_t)0); y < std::min(y2, _height); y++)
        {
            if (add)
                set(x, y, value + get(x, y));
            else
                set(x, y, value);
        }
    }
}

void image::fill_ellipse(double value, size_t x0, size_t y0, size_t a, size_t b, bool add)
{
    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            if ((x - x0) * (x - x0) * b * b + (y - y0) * (y - y0) * a * a <= a * a * b * b)
            {
                if (add)
                    set(x, y, value + get(x, y));
                else
                    set(x, y, value);
            }
        }
    }
}