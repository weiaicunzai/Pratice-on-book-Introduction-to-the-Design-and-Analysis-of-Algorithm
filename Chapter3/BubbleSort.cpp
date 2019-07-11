#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::sort;
using std::swap;


/**
 * @brief sort given array by bubble sort
 * @params arr An array A[0..n − 1] of orderable elements
 * @output arr Array A[0..n − 1] sorted in nondecreasing order
 */
void bubble_sort(vector<int> &arr)
{
    if(arr.size()  <= 1)
        return;

    for(int i = 0; i < arr.size() - 1; i++)
        for(int j = 0; j < arr.size() - 1 - i; j++)
            if(arr[j] > arr[j + 1])
                swap(arr[j + 1], arr[j]);
}

int main()
{
    int array_size = randint(0, 1000);
    vector<int> test;
    for(int i = 0; i < array_size; i++)
        test.push_back(randint(-100000, 100000));
    vector<int> test1 = test;
    
    bubble_sort(test);
    sort(test1.begin(), test1.end()); //test for correctness

    if(test1 == test)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}