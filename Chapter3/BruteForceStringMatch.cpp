#include <algorithm>
#include <iostream>
#include <string>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::string;


/*
 *@brief Implements brute-force string matching
 *@param s a string of n characters representing a text 
 *@param p a string of n characters representing a pattern
 */
int string_matching_bf(const string &s, const string &p)
{
    if(s.size() < p.size())
        return -1;
    
    if(s.empty() || p.empty())
        return -1;    

    for(int i = 0; i < s.size() - p.size() + 1; i++)
    {
        int j = 0;
        while(j < p.size() && s[i + j] == p[j])
            j++;
        if(j == p.size())
            return i;
    }

    return -1;
}

int main()
{

    string s = randstring(randint(0, 1000000));
    string p = randstring(randint(0, 5));

    int index = string_matching_bf(s, p);

    std::size_t found = s.find(p);
    
    if(found == string::npos && index == -1)
        cout << "correct result" << endl;
    else if(found == 0 && p.empty() && index == -1)
        cout << "correct result" << endl;
    else if(found == index)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;

}
