#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::sort;
using std::swap;
using std::vector;

/**
 * @breif partitions a subarray by Hoare’s algorithm, using the first element
   as a pivot
   @param input array
   @param left left indices
   @param right right indices
   @output pivot position
 */
int hoare_partition(vector<int> &arr, const int left, const int right)
{
    if (left > right)
        return -1;

    if (left == right)
        return left;

    int pivot = arr[left];
    int i = left + 1;
    int j = right;

    while (i <= j)
    {
        while (arr[j] > pivot)
            j--;
        while (arr[i] < pivot)
            i++;
        swap(arr[i], arr[j]);
    }

    //the last swap in the while loop was under
    //condition(i >=j) which is illegal, we need
    //to switch back
    swap(arr[i], arr[j]);
    swap(arr[j], arr[left]);
    return j;
}

/**
 * @brief sort an array using quick sort
 * @param left left indices of subarray
 * @param right right indices of subarray
 * @output arr sorted array
 */
void quick_sort(vector<int> &arr, const int left, const int right)
{
    if(left >= right)
        return;

    int p = hoare_partition(arr, left, right);

    quick_sort(arr, left, p - 1);
    quick_sort(arr, p + 1, right);
}

int main()
{
    int size = randint(1, 20);
    vector<int> arr;
    vector<int> arr1;
    while(size--)
        arr.push_back(randint(-20, 20));
    //arr = {1, -5, 20, -9, -8, -20, -2, -14, 10, 13, -13 ,-7 };
    arr1 = arr;

    for(auto x : arr)
    cout << x << " ";
    cout << endl;

    quick_sort(arr, 0, arr.size() - 1);
    for(auto x : arr)
    cout << x << " ";
    cout << endl;
    sort(arr1.begin(), arr1.end());
    for(auto x : arr1)
    cout << x << " ";
    cout << endl;


    if (arr1 == arr)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}
