#include "exemples.h"

/// @brief Validation program to display several examples that demonstrate the validity of the algorithm's implementations
int main()
{
    exemple_fft_1D(1024, 32);
    exemple_fft_2D(1024, 32);
    system("python ../python/intersects.py");
}