#include "save.h"
#include <filesystem>

void save_vector(std::vector<double> data, std::string path)
{
    std::ofstream file(path + ".txt");
    file << data.size() << "\n";
    for (double x : data)
    {
        file << x << "\n";
    }
    file.close();
}

void display_image(image im, double gamma)
{
    size_t index = rand() % 10000;
    std::string name = std::string("temp_image_") + std::to_string(index);
    im.save(name);
    auto error = system((std::string("python3 ../python/display_image.py ") + name + std::string(".txt ") + std::to_string(gamma)).data());
    if (error)
        std::cout << "Python execution failed (trying to display image)" << std::endl;
    error = remove((name + std::string(".txt")).data());
    if (error)
        std::cout << "Automatic image file deletion failed" << std::endl;
}

image load_image_png(std::string path)
{
    std::filesystem::path img_path = path;
    if (img_path.extension() != std::string(".png"))
    {
        std::cout << "ERROR :only loads .png images" << std::endl;
        return image(0, 0);
    }
    system((std::string("python3 ../python/convert_png.py ") + img_path.replace_extension("").c_str()).data());
    std::ifstream img_data(img_path.replace_extension(".txt"));
    size_t width, height;
    img_data >> width;
    img_data >> height;
    image img(width, height);
    for (size_t i = 1; i <= height; i++)
    {
        for (size_t j = 1; j <= width; j++)
        {
            double value;
            img_data >> value;
            img.set(j, i, value);
        }
    }

    return img;
}

image load_image_txt(std::string path)
{
    std::filesystem::path img_path = path;
    if (img_path.extension() != std::string(".txt"))
    {
        std::cout << "ERROR :only loads .png images" << std::endl;
        return image(0, 0);
    }
    std::ifstream img_data(path);
    size_t width, height;
    img_data >> width;
    img_data >> height;
    image img(width, height);
    for (size_t i = 1; i <= height; i++)
    {
        for (size_t j = 1; j <= width; j++)
        {
            double value;
            img_data >> value;
            img.set(j, i, value);
        }
    }

    return img;
}

void display_images(std::vector<image> images, double gamma)
{
    std::string command("python3 ../python/display_image.py ");
    std::vector<std::string> filenames;
    for (image im : images)
    {
        size_t index = rand() % 10000;
        filenames.push_back(std::string("temp_image_") + std::to_string(index));
        im.save(filenames.back());
        command += filenames.back() + ".txt ";
    }
    for (size_t i = 0; i < images.size(); i++)
    {
        command += std::to_string(gamma) + " ";
    }
    auto error = system(command.data());
    if (error)
        std::cout << "Python execution failed (trying to display image)" << std::endl;
    for (auto file : filenames)
    {
        error = remove((file + std::string(".txt")).data());
        if (error)
            std::cout << "Automatic image file deletion failed" << std::endl;
    }
}

void display_images(std::vector<image> images, std::vector<double> gamma)
{
    if (images.size() != gamma.size())
        std::cout << "Error: must provide a single gamma value for all files or a vector of matching size for each image" << std::endl;
    std::string command("python3 ../python/display_image.py ");
    std::vector<std::string> filenames;
    for (image im : images)
    {
        size_t index = rand() % 10000;
        filenames.push_back(std::string("temp_image_") + std::to_string(index));
        im.save(filenames.back());
        command += filenames.back() + std::string(".txt ");
    }
    for (auto g : gamma)
    {
        command += std::to_string(g) + " ";
    }

    auto error = system(command.data());
    if (error)
        std::cout << "Python execution failed (trying to display image)" << std::endl;
    for (auto file : filenames)
    {
        error = remove((file + std::string(".txt")).data());
        if (error)
            std::cout << "Automatic image file deletion failed" << std::endl;
    }
}

void display_plot(std::vector<double> data)
{
    size_t index = rand() % 10000;
    save_vector(data, std::string("temp_vector_") + std::to_string(index));
    auto error = system((std::string("python3 ../python/display_plot.py temp_vector_") + std::to_string(index) + std::string(".txt")).data());
    if (error)
        std::cout << "Python execution failed (trying to display vector)" << std::endl;
    error = remove((std::string("temp_vector_") + std::to_string(index) + std::string(".txt")).data());
    if (error)
        std::cout << "Automatic vector file deletion failed" << std::endl;
}