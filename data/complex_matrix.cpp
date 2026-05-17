#include "complex_matrix.h"

complex_matrix::complex_matrix(size_t width, size_t height) : _width(width), _height(height)
{
    if (width <= 0 || height <= 0)
    {
        std::cout << "Error: invalid image size" << std::endl;
        return;
    }

    _data = std::shared_ptr<complex[]>(new complex[width * height]);
    if (!_data.get())
    {
        std::cout << "Image allocation failed" << std::endl;
    }
}

complex_matrix::complex_matrix(complex_matrix &im)
{
    _width = im.width();
    _height = im.height();
    _data = std::shared_ptr<complex[]>(new complex[_width * _height]());
    if (!_data.get())
    {
        std::cout << "Image allocation failed" << std::endl;
    }
    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            set(x, y, im.get(x, y));
        }
    }
}

complex_matrix::complex_matrix(image im)
{
    _width = im.width();
    _height = im.height();
    _data = std::shared_ptr<complex[]>(new complex[_width * _height]);
    if (!_data.get())
    {
        std::cout << "Image allocation failed" << std::endl;
    }
    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            set(x, y, im.get(x, y));
        }
    }
}

size_t complex_matrix::width()
{
    return _width;
}

size_t complex_matrix::height()
{
    return _height;
}

complex complex_matrix::get(size_t x, size_t y)
{
    if (x < 1 || x > _width || y < 1 || y > _height)
    {
        // std::cout << "Error: invalid image position: (" << x << ", " << y << ") (get)" << std::endl;
        return 0.;
    }
    return _data[(x - 1) + _width * (y - 1)];
}

void complex_matrix::set(size_t x, size_t y, complex value)
{
    if (x < 1 || x > _width || y < 1 || y > _height)
    {
        // std::cout << "Error: invalid image position: (" << x << ", " << y << ") (set)" << std::endl;
        return;
    }
    _data[(x - 1) + _width * (y - 1)] = value;
}

void complex_matrix::increment(size_t x, size_t y, complex value)
{
    if (x < 1 || x > _width || y < 1 || y > _height)
    {
        // std::cout << "Error: invalid image position: (" << x << ", " << y << ") (set)" << std::endl;
        return;
    }
    _data[(x - 1) + _width * (y - 1)] = _data[(x - 1) + _width * (y - 1)] + value;
}

std::vector<complex> complex_matrix::get_column(size_t x)
{
    std::vector<complex> output(_height);
    for (size_t i = 0; i < _height; i++)
    {
        output[i] = get(x, i + 1);
    }
    return output;
}

std::vector<complex> complex_matrix::get_line(size_t y)
{
    std::vector<complex> output(_width);
    for (size_t i = 0; i < _width; i++)
    {
        output[i] = get(i + 1, y);
    }
    return output;
}

void complex_matrix::set_column(std::vector<complex> data, size_t x)
{
    for (size_t i = 0; i < _height; i++)
    {
        set(x, i + 1, data[i]);
    }
}

void complex_matrix::set_line(std::vector<complex> data, size_t y)
{
    std::vector<complex> output(_width);
    for (size_t i = 0; i < _width; i++)
    {
        set(i + 1, y, data[i]);
    }
}

image complex_matrix::real_part_to_image()
{
    image im(_width, _height);
    for (size_t i = 1; i <= _width; i++)
    {
        for (size_t j = 1; j <= _height; j++)
        {
            im.set(i, j, get(i, j).real());
        }
    }
    return im;
}

image complex_matrix::imag_part_to_image()
{
    image im(_width, _height);
    for (size_t i = 1; i <= _width; i++)
    {
        for (size_t j = 1; j <= _height; j++)
        {
            im.set(i, j, get(i, j).imag());
        }
    }
    return im;
}

image complex_matrix::modulus_to_image()
{
    image im(_width, _height);
    for (size_t i = 1; i <= _width; i++)
    {
        for (size_t j = 1; j <= _height; j++)
        {
            im.set(i, j, abs(get(i, j)));
        }
    }
    return im;
}

image complex_matrix::phase_to_image()
{
    image im(_width, _height);
    for (size_t i = 1; i <= _width; i++)
    {
        for (size_t j = 1; j <= _height; j++)
        {
            double phase = std::arg(get(i, j));
            if (phase >= 3.1415)
                phase = -phase;
            im.set(i, j, phase);
        }
    }
    return im;
}

void complex_matrix::apply_elementwise(std::function<complex(complex)> f)
{
    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            set(x, y, f(get(x, y)));
        }
    }
}