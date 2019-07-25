#include <iostream>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;

/**
 * @brief finds the number of binary digits in the binary representation 
 * of a positive decimal integer (recursive version)
 * @input a positve decimal integer
 * @output the number of binary digits in n's binary representation
 */
int binary(int n)
{
    if(n == 1)
        return 0;
    
    return binary( n / 2) + 1;
}

int main()
{
    int n = randint(1, 100);
    cout << "decimal integer: " << n << endl;
    cout << binary(n) << endl;
}