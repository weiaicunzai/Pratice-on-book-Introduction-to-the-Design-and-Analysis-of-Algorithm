#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::find;

/**
 * @brief searches for a given value in a given array by sequential search
 * @params arr An array of n elements 
 * @params k search key
 * @output The index of the first element in A that matches K 
 *         or −1 if there are no matching elements
 *          
 */
int sequential_search(vector<int> arr, int k)
{
    int i = 0;
    while(i < arr.size() && arr[i] != k)
        i++;
    
    if(i < arr.size())
        return i;

    return -1;
}

int main()
{
    int array_size = randint(0, 1000);
    vector<int> test;
    for(int i = 0; i < array_size; i++)
        test.push_back(randint(-100, 100));
    int k = randint(-100, 100);

    int index = sequential_search(test, k);
    auto it = find(test.begin(), test.end(), k); //compare our result with stl result

    if(it == test.end() && index == -1)
        cout << "correct result" << endl;
    else if(index == it - test.begin())
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}