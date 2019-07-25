#include <iostream>
#include "../utils/utils.hpp"


using std::endl;
using std::cout;

/**
 * @brief compute the nth fibonacci number recursively by its definition 
 * @input A nonnegative integer n
 * @output the nth fibonacci number
 */

int f(int n)
{
    if(n <= 1)
        return n;
    
    return f(n-1) + f(n-2);
}

int main()
{
    int n = randint(0, 30);
    cout << "the fibonacci number of " << n << " is: " << f(n) <<endl;
}
 