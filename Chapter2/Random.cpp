#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::vector;

/**
 * @biref generates a sequence of n numbers according to linear congruential method
 * @param n number of integers to generate
 * @param m modulus see https://en.wikipedia.org/wiki/Linear_congruential_generator#Paramet
 *              ers_in_common_use for the number to be choosen in various implementation 
 *              of lcg 
 * @param a multiplier
 * @param b increment
 * @param seed the current time
 * @output A sequence r 1 , . . . , r n of n pseudorandom integers uniformly
           distributed among integer values between 0 and m − 1
 */
void random(vector<int> &result, int n, int m = pow(2, sizeof(size_t)), int a = 5, int b = 1, long long seed = std::time(0))
{
    for(int i = 0; i < n; i++)
    {
        seed = (seed * a + b) % m;
        result.push_back(seed);
    }
}

int main()
{
    std::time_t t = std::time(0);

    vector<int> res;
    int size = randint(1, 100);
    random(res, size);

    //this should print a sequence of n numbers between 0 and 1
    for(auto x : res)
        cout << x / (float)(pow(2, sizeof(size_t))) << endl;
}