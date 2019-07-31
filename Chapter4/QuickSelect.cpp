#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::for_each;
using std::vector;
using std::swap;
using std::string;
using std::to_string;

/**
 * @biref parition algorithm using lomuto algorithm
 * @param array
 * @left left indices
 * @right right indices
 * @output new pivot position
 */
int parition(vector<int> &arr, const int left, const int right)
{
    if(arr.empty())
        return -1;
    
    int pivot = arr[left];
    int s = left;

    for(int i = left + 1; i <= right; i++)
        if(pivot > arr[i])
            swap(arr[++s], arr[i]);
    
    swap(arr[s], arr[left]);

    return s;
}

/**
 * @brief find the smallest kth elements in the array
 * @param arr subarray[left, right] of array[0, n-1], defined by its left and right
 *        indices
 * @param K Kth smallest element
 * @output the value of Kth smallest element
 */
int quick_select(vector<int> &arr, const int left, const int right, const int K)
{
    
    if(!(K >= 1))
        throw std::invalid_argument("K should be larger than 0, while K: " + to_string(K));
    if(!(left >= 0 && right >= left && arr.size() - 1 >= right))
        throw std::invalid_argument("0 <= left <= right <= arr.size() - 1");
    if(arr.empty())
        throw std::invalid_argument("array should not be empty");
    
    int s = parition(arr, left, right);
    if(s == -1)
        throw std::invalid_argument("array is empty!");

    if(s + 1 == K)
        return arr[s];
    else if(s + 1 < K)
        return quick_select(arr, s + 1, right, K);
    else
        return quick_select(arr, left, s - 1, K);
}

int main()
{
    int n = randint(1, 15);
    int Kth = randint(1, n);
    vector<int> arr;
    while(n--)
        arr.push_back(randint(-10, 10));
    
    //average time complexity O(n)
    //worest time complexity O(n^2)
    //best time complexity O(n)
    int value = quick_select(arr, 0, arr.size() - 1, Kth);

    cout << "for array : ";
    for_each(arr.begin(), arr.end(), [](int x){cout << x << " ";});
    cout << endl;

    cout << "the " << Kth << " smallest number is " << value << endl;

}