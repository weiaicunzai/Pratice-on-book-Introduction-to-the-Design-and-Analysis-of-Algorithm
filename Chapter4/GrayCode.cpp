#include <iostream>
#include <algorithm>
#include <bitset>
#include <string>
#include <vector>
#include "../utils/utils.hpp"

using std::endl;
using std::cout;
using std::bitset;
using std::vector;
using std::string;
using std::reverse;
using std::make_move_iterator;

/**
 * @brief Generates recursively the binary reflected Gray code of order n
 * @param n  positive integer
 * @output bit_strings a list of all generated bit strings of length n
 *         composing the Gray Code
 */
void brgc(const int n, vector<string> &bit_strings)
{
    if(n <= 0)
        throw "n should be a positive integer";

    auto add_prefix = [](const string p, vector<string> &s)
    {
        for(auto it = s.begin(); it != s.end(); it++)
            *it = p + *it;
    };

    if(n == 1)
    {
        bit_strings.push_back("0");
        bit_strings.push_back("1");
        return;
    }
    else
    {
        //generate list L1 of bit strings of size n − 1 by calling BRGC(n − 1)
        brgc(n - 1, bit_strings);

        //copy list L1 to list L2 in reversed order
        vector<string>l2 = bit_strings;  
        reverse(l2.begin(), l2.end());  

        //add 0 in front of each bit string in list L1
        add_prefix("0", bit_strings);  

        //add 1 in front of each bit string in list L2
        add_prefix("1", l2);

        //append L2 to L1 to get list L
        bit_strings.insert(
            bit_strings.end(), 
            make_move_iterator(l2.begin()),
            make_move_iterator(l2.end())
            );
    }
}
int main()
{

    vector<string> res;
    int n = randint(1, 10);
    brgc(n, res);

    for(auto x : res)
        cout << x << endl;

    cout << "the gray code for number " << n << " is: " << endl;
    cout << "size: " << res.size() << endl;
}
