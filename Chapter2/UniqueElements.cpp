#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::vector;
using std::for_each;


/**
 * @brief determines wheter all the elements in a given array are distinct
 * @param arr an array
 * @output returns true if all the elements in A are distinct and false otherwise
 */
bool unique_element(const vector<int> &arr)
{
    for(auto it = arr.begin(); it != arr.end() - 1; it++)
        for(auto it1 = it + 1; it1 != arr.end(); it1++)
            if(*it == *it1)
                return false;
    
    return true;
}

int main()
{
    int arr_size = randint(1, 10);
    vector<int> arr;
    for(int i = 0; i < arr_size; i++)
        arr.push_back(randint(-10, 10));
    
    cout << unique_element(arr) << endl;

    cout << endl;
    for_each(arr.begin(), arr.end(), [](int n){cout << n << endl;});
}
