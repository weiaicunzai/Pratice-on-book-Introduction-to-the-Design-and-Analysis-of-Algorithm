#include <algorithm>
#include <iostream>
#include <vector>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::vector;
using std::swap;
using std::reverse;

/**
 * @brief permutation has two consecutive elements in increasing order
 * @perm one permutation
 * @output true if the permutation has two consecutive elements in 
 *         increasing order
 */
bool is_increasing(const vector<int> &perm)
{
    for(auto it = perm.begin(); it != perm.end() - 1; it++)
        if(*it < *(it + 1))
            return true;
    return false;
}

/**
 * @brief largest index such that a i < a i+1 //a i+1 > a i+2 > . . . > a n
 * @param perm a permuation
 * @output the largest index i
 */
int largest_index(const vector<int> &perm)
{
    auto i = perm.begin();
    for(auto it = perm.begin(); it != perm.end() - 1; it++)
        if(*it < *(it + 1))
            i = it;
    
    return  i - perm.begin();
}

/**
 * @brief find the largest index j such that a i < a j //j ≥ i + 1 since a i < a i+1
 * @param perm a permutation
 * @param the largest index j such that a i < a j
 * @output the index j
 */
int larger_than(const vector<int> &perm, const int i)
{
    auto j = perm.begin() + i + 1;
    for(auto it = perm.begin() + i + 1; it != perm.end(); it++)
        if(*it > *(perm.begin() + i))
            j = it;
    
    return j - perm.begin();
}

/**
 * @brief Generates permutations in lexicographic order
 * @param n a positive integer 
 * @output all permutations in lexicographic order
 */
void lexicographic_perm(int n, vector<vector<int>> &perms)
{
    if(n < 1)
        throw "n should be larger than 0";

    vector<int> perm;
    for(int i = 1; i <= n; i++)
        perm.push_back(i);
    perms.push_back(perm);
        
    while(is_increasing(perm))
    {
        int i = largest_index(perm);  //let i be its largest index such that a i < a i+1
        int j = larger_than(perm, i);  //find the largest index j such that a i < a j
        swap(perm[i], perm[j]);  //swap a i with a j
        reverse(perm.begin() + i + 1, perm.end());  //reverse the order of the elements from a 
                                                    //i+1 to a n inclusive
        perms.push_back(perm);
    }
}

int main()
{
    vector<vector<int>> perm;
    int n = randint(1, 6);
    lexicographic_perm(n, perm);

    cout << "the total permutation numbers are : " << perm.size() << " for number " << n << endl;
    for(auto x : perm)
    {
        for(auto a : x)
            cout << a;
        cout << endl;
    }
}