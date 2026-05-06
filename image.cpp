#include "image.h"

image::image(size_t width, size_t height) : _width(width), _height(height)
{
    if (width <= 0 || height <= 0)
    {
        std::cout << "Error: invalid image size" << std::endl;
        return;
    }

    _data = std::shared_ptr<double[]>(new double[width * height]);
    if (!_data.get())
    {
        std::cout << "Image allocation failed" << std::endl;
    }
}

size_t image::width()
{
    return _width;
}

size_t image::height()
{
    return _height;
}

double image::get(size_t x, size_t y)
{
    if (x < 1 || x > _width || y < 1 || y > _height)
    {
        std::cout << "Error: invalid image position: (" << x << ", " << y << ") (get)" << std::endl;
        return 0.;
    }
    return _data[(x - 1) + _width * (y - 1)];
}

void image::set(size_t x, size_t y, double value)
{
    if (x < 1 || x > _width || y < 1 || y > _height)
    {
        std::cout << "Error: invalid image position: (" << x << ", " << y << ") (set)" << std::endl;
        return;
    }
    _data[(x - 1) + _width * (y - 1)] = value;
}

void image::save(std::string path)
{
    if (!_data.get())
    {
        std::cout << "No image data to save" << std::endl;
        return;
    }
    std::ofstream file(path + ".txt");

    file << _width << "\n";
    file << _height << "\n";

    for (size_t y = 1; y <= _height; y++)
    {
        for (size_t x = 1; x <= _width; x++)
        {
            // to optimize
            file << get(x, y) << "\n";
        }
    }

    file.close();
}

void image::apply_elementwise(std::function<double(double)> f)
{
    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            set(x, y, f(get(x, y)));
        }
    }
}

void image::fill_uniform(double value)
{
    for (size_t x = 1; x <= _width; x++)
    {
        for (size_t y = 1; y <= _height; y++)
        {
            set(x, y, value);
        }
    }
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

void image::fill_phantom(size_t x0, size_t y0, size_t size, bool high_contrast, bool overwrite)
{
    if (overwrite)
        fill_uniform(0);

    double dark, grey, light;
    if (high_contrast)
    {
        dark = -.8;
        grey = -.2;
        light = .1;
    }
    else
    {
        dark = -.49;
        grey = -0.01;
        light = 0.005;
    }
    fill_ellipse(1, x0, y0, size * .375, size * .5);
    fill_ellipse(dark, x0, y0 + size * .01, size * 0.36, size * .475);

    fill_ellipse(grey, x0 + size * .112, y0, size * .06, size * .168);
    fill_ellipse(grey, x0 - size * .112, y0, size * .087, size * .223);

    fill_ellipse(light, x0, y0 - size * .19, size * .114, size * 0.136);

    fill_ellipse(light, x0, y0 + size * .054, size * .025, size * .025);
    fill_ellipse(light, x0, y0 - size * .054, size * .025, size * .025);

    fill_ellipse(light, x0 - size * .043, y0 + size * .329, size * .025, size * .013);
    fill_ellipse(light, x0, y0 + size * .329, size * .013, size * .013);
    fill_ellipse(light, x0 + size * .033, y0 + size * .329, size * .013, size * .025);
}