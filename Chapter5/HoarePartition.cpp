#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::string;
using std::swap;
using std::vector;

const string red("\033[0;4;31m");
const std::string reset("\033[0m");

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

    while (i < j)
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

int main()
{
    int size = randint(1, 20);
    vector<int> arr;
    while (size--)
        arr.push_back(randint(-100, 100));

    int p = hoare_partition(arr, 0, arr.size() - 1);

    for (int i = 0; i < arr.size(); i++)
        if (i == p)
            cout << red << arr[i] << " " << reset;
        else
            cout << arr[i] << " ";
    cout << endl;
}