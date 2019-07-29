#include <list>
#include <iostream>
#include <vector>
#include <cmath>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::vector;
using std::sqrt;

/**
 * @biref Implements the sieve of Eratosthenes
 * @param n positive integers which is larger than 1(n > 1)
 * @output res an array of all prime numbers less or equal to n 
 */
void sieve(int n, vector<int>& res)
{
    if(n < 2)
        throw "n should be larger than 1";

    vector<int> temp;
    for(int i = 2; i <= n; i++)
        temp.push_back(i);
    
    for(auto x = temp.begin(); x != temp.begin() + (int)sqrt(n) - 1; x++)
    {
        if(*x != 0)
        {
            auto j = temp.begin() + *x * *x - 2;
            while(j < temp.end())
            {
                *j = 0;   //mark element as eliminated
                j += *x;
            }
        }
    }

    for(auto x : temp)
        if(x)
            res.push_back(x);
}

int main()
{
    vector<int> res;
    int n = randint(2, 1000);
    sieve(n, res);

    cout << "prime numbers between 2 and " << n  << " are: " << endl;
    for(auto x : res)
        cout << x << endl;
}