#include <iostream>
#include <vector>


using std::cout;
using std::endl;
using std::vector;
using std::swap;

const bool r2l = true;
const bool l2r = false;

/**
 * @brief check whether the permutation has a mobile element
 * @params arr the last permutation array
 * @params dir direction array
 */
bool has_mobile(const vector<int> &arr, const vector<bool> &dir)
{
    for(int i = 0; i < arr.size(); i++)
    {
        //when an integer has left to right direction
        if(dir[i] == l2r && i + 1 < dir.size())
            if(arr[i] > arr[i + 1])
                return true;
        
        //when an integer has right to left direction
        if(dir[i] == r2l && i - 1 >= 0)
            if(arr[i] > arr[i - 1])
                return true;
    }

    return false;
}

/**
 * @brief find the largest mobile elements of a permutation
 * @param arr the last permutation array
 * @param dir the direction array
 * @return the index of the largest mobile elements
 */
int largest_mobile(const vector<int> &arr, const vector<bool> &dir)
{
    int max_index = -1;
    for(int i = 0; i < arr.size(); i++)
    {
        //when an integer has left to right direction
        if(dir[i] == l2r && i + 1 < dir.size())
            if(arr[i] > arr[i + 1] && (max_index == -1 || arr[i] > arr[max_index]))
                max_index = i;
        
        //when an integer has right to left direction
        if(dir[i] == r2l && i - 1 >= 0)
            if(arr[i] > arr[i - 1] && (max_index == -1 || arr[i] > arr[max_index]))
                max_index = i;
    }

    return max_index;
}

/**
 * @brief swap the largest element with the adjacent element k's arrow points to
 * @output arr the last permutation array
 * @output dir the direction array
 * @param largest_index largest element index 
 */
void swap_largest(vector<int> &arr, vector<bool> &dir, int &largest_index)
{
    int k_, k = largest_index;
    if(dir[k] == r2l)
        k_ = k - 1;
    else
        k_ = k + 1;
    
    swap(arr[k], arr[k_]);
    swap(dir[k], dir[k_]);

    largest_index = k_;
}

/**
 * @breif reverse the direction of all the elements that larger than k
 * @param arr permutation array
 * @output dir direction array
 * @param largest_index largest element's index
 */
void reverse_larger_than(const vector<int> &arr, vector<bool> &dir, const int largest_index)
{
    int k = largest_index;
    for(int i = 0; i < dir.size(); i++)
        if(arr[i] > arr[k])
            dir[i] = !dir[i];
}

/**
 * @brief calculates the factorial of n
 * @param n the integer we want to calculate
 * @return n! factorial of n
 */
int factorial(int n)
{
    int res = n;
    for(int i = 1; i < n; i++)
        res = res * i;
    
    return res;
}

/**
 * @brief Implements Johnson-Trotter algorithm for generating permutations
 * @param n A positive integer n
 * @param data output A list of all permutations of {1, . . . , n}
 */
void johnson_trotter(int n, vector<vector<int>> &permutations)
{
    if(n < 1)
        throw "n should be larger than 0";

    vector<int> perm(n);
    vector<bool> dir(n);

    //initialize the first permutation with 1 2 . . . n(all integers'
    //directions are right to left)
    for(int i = 0; i < n; i++)
        perm[i] = i + 1;
    for(int i = 0; i < n; i++)
        dir[i] = r2l;
    
    permutations.push_back(perm);

    //while the last permutation has a mobile element do
    while(has_mobile(perm, dir))
    {
        //find its largest mobile element k
        int largest_index = largest_mobile(perm, dir);

        if(largest_index < 0)
        {
            cout << "wrong largest index" << endl;
            return;
        }

        //swap k with the adjacent element k’s arrow points to
        swap_largest(perm, dir, largest_index);

        //reverse the direction of all the elements that are larger than k
        reverse_larger_than(perm, dir, largest_index);

        //add the new permutation to the list
        permutations.push_back(perm);
    }
}

int main()
{
    vector<vector<int>> res;
    johnson_trotter(6, res);

    //print result
    cout << res.size() << endl;
    for(auto x : res)
    {
        for(auto y : x)
            cout << y << " ";
        cout << endl;
    }
}