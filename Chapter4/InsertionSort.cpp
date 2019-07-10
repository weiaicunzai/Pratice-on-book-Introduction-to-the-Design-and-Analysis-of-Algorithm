#include <vector>
#include <iostream>
#include <algorithm>
#include "../utils/utils.hpp"

using std::vector;
using std::cout;
using std::endl;
using std::sort;


/**
 * @brief Sorts a given array by insertion sort
 * @param arr an array A[0..n − 1] of n orderable elements
 * @output arr array A[0..n-1] sorted in nondecreasing order
 */
void insertion_sort(vector<int> &arr)
{
    if(arr.size() <= 1)
        return;
    
    for(int i = 1; i < arr.size(); i++)
    {
        int v = arr[i];
        int j = i - 1;
        while(j >= 0 && arr[j] > v)
        {
            //move jth element one position right 
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = v;
    }
}

int main()
{
    int array_size = randint(0, 1000);
    vector<int> test;
    for(int i = 0; i < array_size; i++)
        test.push_back(randint(-100000, 100000));
    vector<int> test1 = test;
    
    insertion_sort(test);
    sort(test1.begin(), test1.end());

    if(test1 == test)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}



