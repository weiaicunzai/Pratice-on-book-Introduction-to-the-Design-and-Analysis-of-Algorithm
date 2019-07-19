#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::vector;
using std::cout;
using std::endl;


/**
 * @brief Determines the value of the largest element in a given array
 * @params arr the given arr of integers
 * @params output the value of the largest element in arr
 */
int max_element(const vector<int> &arr)
{
    if(arr.size() < 1)
        throw "array size should be larger than one";
    
    int max_value = arr[0];
    for(int i = 0; i < arr.size(); i++)
        if(arr[i] > max_value)
            max_value = arr[i];
    
    return max_value;
}

int main()
{
    int arr_size = randint(1, 1000);
    vector<int> arr;
    for(int i = 0; i < arr_size; i++)
        arr.push_back(randint(-1000, 1000));
    
    if(max_element(arr) != *std::max_element(arr.begin(), arr.end()))
        cout << "wrong result" << endl;
    else
        cout << "correct result" << endl;
}


