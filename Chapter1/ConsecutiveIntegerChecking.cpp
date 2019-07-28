#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::min;

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