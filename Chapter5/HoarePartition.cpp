/**
 * (1)Hoare’s scheme is more efficient than Lomuto’s partition scheme 
 * because it does three times fewer swaps on average, and it creates 
 * efficient partitions even when all values are equal.
 * 
 * (2)Like Lomuto’s partition scheme, Hoare partitioning also causes 
 * Quicksort to degrade to O(n^2) when the input array is already sorted, 
 * it also doesn’t produce a stable sort.
 * 
 * (3)Note that in this scheme, the pivot’s final location is not necessarily 
 * at the index that was returned, and the next two segments that the main 
 * algorithm recurs on are (lo..p) and (p+1..hi) as opposed to (lo..p-1) and 
 * (p+1..hi) as in Lomuto’s scheme.
 */
#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::max;
using std::min;
using std::string;
using std::swap;
using std::vector;

const string red("\033[0;4;31m");
const string reset("\033[0m");

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
        throw "left should be larger than right";

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

int main()
{
    int size = randint(1, 20);
    vector<int> arr;
    while (size--)
        arr.push_back(randint(-10, 10));

    int p = hoare_partition(arr, 0, arr.size() - 1);

    //right part is always larger than the left part
    for (int i = 0; i < arr.size(); i++)
        if (i >= p)
            cout << red << arr[i] << " ";
        else
            cout << arr[i] << " ";
    cout << endl;
}