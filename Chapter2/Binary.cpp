#include <iostream>
#include <bitset>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::bitset;

/**
 * @brief finds the number of binary digits in the binary representation of a positive
 * decimal integer 
 * @input a positve decimal integer
 * @output the number of binary digits in n's binary representation
 */
int binary(int n)
{
    int count = 0;
    while(n > 1)
    {
        count++;
        n = n / 2;
    }
    
    return count;
}

int main()
{
    int n = randint(1, 100);
    cout << "decimal integer: " << n << endl;
    cout << binary(n) << endl;
}