#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::min;

/**
 * @brief Consecutive integer checking algorithm for computing gcd(m, n)
 * @param  two input integer m and n, both should be larget than 1
 * @output  the greatest common divisor of m and n
 */
int gcd(int m, int n)
{
    if(!m or !n)
        throw "input integers should be larger than 0";

    int t = min(m, n);

    while(!(m % t == 0 && n % t == 0)) 
        t--;
    
    return t;
}

int main()
{
    int m = randint(1, 30);
    int n = randint(1, 30);
    cout << "two integers are : " << m  << " and " << n << endl;
    cout << "the gcd is: " << gcd(m, n) << endl;
}