#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <chrono>
#include <unordered_map>

using namespace std::chrono;

struct timer_data
{
    high_resolution_clock::time_point t0;
    double offset = 0.;
    bool running = true;
};

class timer
{
public:
    static void start_watch(const char *name = "global")
    {
        watches.insert_or_assign(name, timer_data{high_resolution_clock::now()});
    }

    static void pause_watch(const char *name = "global")
    {
        if (!watches.contains(name))
            std::cout << "ERROR: trying to pause a watch that hasn't been created" << std::endl;
        else
        {
            auto &watch = watches.at(name);
            watch.offset += duration_cast<nanoseconds>(high_resolution_clock::now() - watch.t0).count() * .000001;
            watch.running = false;
        }
    }

    static void continue_watch(const char *name = "global")
    {
        auto t = high_resolution_clock::now();
        if (!watches.contains(name))
            watches.emplace(name, timer_data{t, 0.});
        else
        {
            auto &watch = watches.at(name);
            if (watch.running)
                return;
            watches.at(name).t0 = t;
            watches.at(name).running = true;
        }
    }

    static void print_ellapsed_time(const char *name = "global")
    {
        auto t = high_resolution_clock::now();
        if (!watches.contains(name))
            std::cout << "ERROR: trying to print the time of a watch that hasn't been created" << std::endl;
        else
        {
            double dt = watches.at(name).offset;
            if (watches.at(name).running)
                dt += duration_cast<nanoseconds>(t - watches.at(name).t0).count() * .000001;
            std::cout << "Time since watch `" << name << "` start: " << dt << "ms" << std::endl;
        }
    }

    static double get_ellapsed_time(const char *name = "global")
    {
        auto t = high_resolution_clock::now();
        if (!watches.contains(name))
        {
            std::cout << "ERROR: trying to get the time of a watch that hasn't been created" << std::endl;
            return 0.;
        }
        else
        {
            double dt = watches.at(name).offset;
            if (watches.at(name).running)
                dt += duration_cast<nanoseconds>(t - watches.at(name).t0).count() * .000001;
            return dt;
        }
    }

private:
    static inline std::unordered_map<std::string, timer_data> watches;
};