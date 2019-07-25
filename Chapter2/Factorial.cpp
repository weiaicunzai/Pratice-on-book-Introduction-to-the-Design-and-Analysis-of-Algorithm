#include <iostream>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;

/**
 * @biref Computes n! recursively 
 * @param n a nonegative integer n
 * @output the value of n!
 */
int f(int n)
{
    if(!n)
        return 1;
    
    return f(n-1) * n;
}

int main()
{
    int n = randint(0, 10);
    cout << "the factorial of " << n << " is " << f(n) << endl;
}