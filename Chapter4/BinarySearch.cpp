#include <iostream>
#include <vector>
#include <algorithm>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::vector;
using std::sort;
using std::for_each;
using std::find;

/**
 * @brief implments nonrecursive binary search
 * @param arr an sorted array in ascending order
 * @param k the search key
 * @output index of the array's element that is
 *          equal to K or -1 if there is no such 
 *          element
 */
int binary_search(vector<int> &arr, const int K)
{
    if(arr.empty())
        return -1;
    
    int low = 0;
    int hight = arr.size() - 1;
    int mid = (low + hight) / 2;

    while(low <= hight)
    {
        if(arr[mid] == K)
            return mid;
        if(arr[mid] < K)
            low = mid + 1;
        if(arr[mid] > K)
            hight = mid - 1;
        
        mid = (low + hight) / 2;
    }

    return -1;
}

int main()
{
    //init arr
    vector<int> arr;
    int size = randint(0, 100);
    while(size--)
        arr.push_back(randint(-200, 200));

    sort(arr.begin(), arr.end());  

    int K = randint(-200, 200);
    int index = binary_search(arr, K);
    auto it = find(arr.begin(), arr.end(), K);

    if(it == arr.end() && index == -1)
        cout << "right result" << endl;
    else if(it - arr.begin() == index)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}