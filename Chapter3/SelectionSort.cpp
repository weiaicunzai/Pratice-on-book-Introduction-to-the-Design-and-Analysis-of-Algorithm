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
 * @brief sort given array by selection sort
 * @params arr An array A[0..n − 1] of orderable elements
 * @output arr Array A[0..n − 1] sorted in nondecreasing order
 */
void selection_sort(vector<int> &arr)
{
    if(arr.size()  <= 1)
        return;

    for(int i = 0; i < arr.size() - 1; i++)
    {
        int min_index = i;
        for(int j = i + 1; j < arr.size(); j++)
            if(arr[j] < arr[min_index])
                min_index = j;

        swap(arr[min_index], arr[i]);
    }
}

int main()
{
    int array_size = randint(0, 1000);
    vector<int> test;
    for(int i = 0; i < array_size; i++)
        test.push_back(randint(-100000, 100000));
    vector<int> test1 = test;
    
    selection_sort(test);
    sort(test1.begin(), test1.end()); //test for correctness

    if(test1 == test)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}