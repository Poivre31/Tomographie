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
    }

    static void print_ellapsed_time()
    {
        auto t1 = high_resolution_clock::now();
        std::cout << "Time since watch start: " << duration_cast<milliseconds>(t1 - t0).count() << "ms" << std::endl;
    }

private:
    static inline _V2::high_resolution_clock::time_point t0;
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

void display_image(image im)
{
    size_t index = rand() % 10000;
    im.save(std::string("temp_image_") + std::to_string(index));
    auto error = system((std::string("python ../python/display_image.py temp_image_") + std::to_string(index) + std::string(".txt")).data());
    if (error)
        std::cout << "Python execution failed (trying to display image)" << std::endl;
    remove((std::string("temp_image_") + std::to_string(index) + std::string(".txt")).data());
}

void display_plot(std::vector<double> data)
{
    size_t index = rand() % 10000;
    save_vector(data, std::string("temp_vector_") + std::to_string(index));
    auto error = system((std::string("python ../python/display_plot.py temp_vector_") + std::to_string(index) + std::string(".txt")).data());
    if (error)
        std::cout << "Python execution failed (trying to display vector)" << std::endl;
    remove((std::string("temp_vector_") + std::to_string(index) + std::string(".txt")).data());
}