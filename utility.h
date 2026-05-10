#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std::chrono;

class timer
{
public:
    static void start_watch()
    {
        t0 = high_resolution_clock::now();
        offset = 0.;
    }

    static void pause_watch()
    {
        offset += duration_cast<milliseconds>(high_resolution_clock::now() - t0).count();
    }

    static void continue_watch()
    {
        t0 = high_resolution_clock::now();
    }

    static void print_ellapsed_time()
    {
        auto t1 = high_resolution_clock::now();
        std::cout << "Time since watch start: " << duration_cast<milliseconds>(t1 - t0).count() + offset << "ms" << std::endl;
    }

private:
    static inline high_resolution_clock::time_point t0;
    static inline double offset = 0.;
};

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

void display_image(image im, double gamma = 1)
{
    size_t index = rand() % 10000;
    std::string name = std::string("temp_image_") + std::to_string(index);
    im.save(name);
    auto error = system((std::string("python3.14 ../python/display_image.py ") + name + std::string(".txt ") + std::to_string(gamma)).data());
    if (error)
        std::cout << "Python execution failed (trying to display image)" << std::endl;
    error = remove((name + std::string(".txt")).data());
    if (error)
        std::cout << "Automatic image file deletion failed" << std::endl;
}

void display_images(std::vector<image> images, double gamma = 1)
{
    std::string command("python3.14 ../python/display_image.py ");
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
    std::string command("python3.14 ../python/display_image.py ");
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
    auto error = system((std::string("python3.14 ../python/display_plot.py temp_vector_") + std::to_string(index) + std::string(".txt")).data());
    if (error)
        std::cout << "Python execution failed (trying to display vector)" << std::endl;
    error = remove((std::string("temp_vector_") + std::to_string(index) + std::string(".txt")).data());
    if (error)
        std::cout << "Automatic vector file deletion failed" << std::endl;
}