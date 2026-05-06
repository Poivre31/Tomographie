#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <chrono>

using namespace std::chrono;

class timer
{
public:
    void start_watch()
    {
        t0 = high_resolution_clock::now();
    }

    void print_ellapsed_time()
    {
        auto t1 = high_resolution_clock::now();
        std::cout << "Time since watch start: " << duration_cast<milliseconds>(t1 - t0).count() << "ms" << std::endl;
    }

private:
    _V2::high_resolution_clock::time_point t0;
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