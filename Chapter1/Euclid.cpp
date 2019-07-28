#include <iostream>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;

int euclid(int m, int n)
{
    if(!m && !n)
        throw "m and n can not both be 0";
    if(m < 0)
        throw "m should be nonnegative";
    if(n < 0)
        throw "n should be nonnegative";

    while(n)
    {
        int temp = n;
        n = m % n;
        m = temp;
    }

    return m;
}

int main()
{
    int m = randint(0, 100);
    int n = randint(0, 100);

    cout << "the gcd of " 
         << m << " and " << n 
         << " is " << euclid(m, n) << endl;
}