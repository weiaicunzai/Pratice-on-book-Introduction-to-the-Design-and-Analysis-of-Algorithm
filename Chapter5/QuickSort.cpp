#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::max;
using std::min;
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

    int mid = (left + right) / 2;
    int median = max(min(arr[left], arr[right]), min(max(arr[left], arr[right]), arr[mid]));

    int l = left;
    int r = right;
    while (l <= r)
    {
        while (arr[l] < median && l <= r)
            l++;
        while (arr[r] > median)
            r--;

        if (l <= r)
            swap(arr[l++], arr[r--]);
    }
    return l;
}

/**
 * @brief sort an array using quick sort
 * @param left left indices of subarray
 * @param right right indices of subarray
 * @output arr sorted array
 */
void quick_sort(vector<int> &arr, const int left, const int right)
{
    if (left >= right)
        return;

    int p = hoare_partition(arr, left, right);

    quick_sort(arr, left, p - 1);
    quick_sort(arr, p, right);
}

int main()
{
    int size = randint(1, 20);
    vector<int> arr;
    vector<int> arr1;
    while (size--)
        arr.push_back(randint(-20, 20));
    arr1 = arr;

    quick_sort(arr, 0, arr.size() - 1);
    sort(arr1.begin(), arr1.end());

    if (arr1 == arr)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}
