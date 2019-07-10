#include <random>
#include <iostream>

using std::random_device;
using std::mt19937;
using std::vector;
using std::uniform_int_distribution;

int randint(int min, int max) //[min, max]
{
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist(min, max); // distribution in range [1, 6]

    return dist(rng);
}

