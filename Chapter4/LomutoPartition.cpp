#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::vector;

const string red("\033[0;4;31m");
const string reset("\033[0m");

/**
 * Partitions subarray by Lomuto’s algorithm using first element as pivot
 * @param: A subarray A[l..r] of array A[0..n − 1], defined by its 
 *         indices l and r left and right (l ≤ r)
 * @param: Partition of A[l..r] and the new position of the pivot
 */
int lomuto_parition(vector<int> &arr)
{
    if (arr.size() < 1)
        return -1;

    int pivot = arr[0];
    int left = 0;
    int right = arr.size() - 1;

    int s = left;
    for (int i = left + 1; i <= right; i++)
        if (arr[i] < pivot)
            swap(arr[i], arr[++s]);

    swap(arr[left], arr[s]);

    return s;
}

int main()
{
    int size = randint(1, 15);

    vector<int> arr;
    while (size--)
        arr.push_back(randint(-10, 10));

    int pivot = lomuto_parition(arr);

    if(pivot == -1)
    {
        cout << "array size should be larger than 0" << endl;
        return;
    }

    //red is pivot
    for (auto it = arr.begin(); it != arr.end(); it++)
        if (it - arr.begin() == pivot)
            cout << red << *it << " " << reset;
        else
            cout << *it << " ";

    cout << endl;
}