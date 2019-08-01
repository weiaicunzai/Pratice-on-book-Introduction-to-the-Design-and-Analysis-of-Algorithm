#include <vector>
#include <iostream>
#include "../utils/utils.hpp"

using std::copy;
using std::cout;
using std::endl;
using std::sort;
using std::vector;

/**
 * @brief Merges two sorted arrays into one sorted array
 * @param arr sorted array
 * @param left left -> mid is the left part we need to merge
 * @param right mid + 1 -> right is the right part we need to merge
 * @ouptut arr, left - > right are merged
 */
void merge(vector<int> &arr, const int left, const int right)
{
    vector<int> out;
    int mid = (left + right) / 2;

    int i = left;
    int j = mid + 1;
    while (i <= mid && j <= right)
        if (arr[i] < arr[j])
            out.push_back(arr[i++]);
        else
            out.push_back(arr[j++]);

    while (i <= mid)
        out.push_back(arr[i++]);
    while (j <= right)
        out.push_back(arr[j++]);

    //copy out array back to a and b
    copy(out.begin(), out.begin() + mid - left + 1, arr.begin() + left);
    copy(out.begin() + mid - left + 1, out.end(), arr.begin() + mid + 1);
}

/**
 * @brief sort an array using merge sort
 * @param left left indice that start to sort
 * @param right right indice that stop sorting
 * @output arr sorted array
 */
void merge_sort(vector<int> &arr, const int left, const int right)
{
    if (left == right)
        return;

    int mid = (left + right) / 2;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, right);
}

int main()
{
    int size = randint(1, 30);
    vector<int> arr;
    while (size--)
        arr.push_back(randint(-30, 30));
    vector<int> arr1 = arr;

    merge_sort(arr, 0, arr.size() - 1);
    sort(arr1.begin(), arr1.end());

    if (arr == arr1)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}