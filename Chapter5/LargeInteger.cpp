#include <iostream>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::stod;
using std::stold;
using std::string;
using std::to_string;

/**
 * @brief pad shorter string with leading 0 to make two strings same length
 * @param first string a
 * @param second string b
 */
void padding(string &first, string &second)
{
    if (first.size() == second.size())
        return;

    if (first.size() > second.size())
        second.insert(0, first.size() - second.size(), '0');
    else
        first.insert(0, second.size() - first.size(), '0');
}

/**
 * @brief addition for bit string
 * @param first string
 * @param second string
 * @output string addition result for first + second
 */
string str_addition(string first, string second)
{
    string result;

    //pad the shorter string
    padding(first, second);
    int carry = 0;

    for (int i = first.size() - 1; i >= 0; i--)
    {
        int first_bit = first.at(i) - '0';
        int second_bit = second.at(i) - '0';
        int sum = first_bit + second_bit + carry;

        result = to_string(sum).back() + result;

        if (sum >= 10)
            carry = 1;
        else
            carry = 0;
    }

    if (carry)
        result = '1' + result;

    return result;
}

/**
 * @brief subtraction for bit string
 * @param first integer in string format
 * @param second integer in string format first should be larger than second
 * @output return the result of integer subtraction
 *         in string format
 */
string str_subtraction(string first, string second)
{
    //check input
    padding(first, second);
    for (int i = 0; i < first.size(); i++)
        if (first[i] > second[i])
            break;
        else if (first[i] < second[i])
            throw "first integer should be larger than the second";

    string result;

    int carry = 0;
    for (int i = first.size() - 1; i >= 0; i--)
    {
        int diff = first.at(i) - second.at(i) - carry;

        if (diff < 0)
        {
            diff += 10;
            carry = 1;
        }
        else
            carry = 0;
        result = to_string(diff) + result;
    }

    return result;
}

/**
 * @brief right shift a string with appending 0
 * @param digits  how many digits we want to right shift
 * @output return a right shifted string
 */
string str_right_shift(string str, const int digits)
{
    return str.insert(str.size(), digits, '0');
}

/**
 * @brief karatsuba implementation, multiplication two large integers
 *        for simplicity reason, we only consider positive integer 
 *        muliplication
 * @param first large integer in string format
 * @param second large integer in string format
 * @output result of multiplication in string format
 */
string karatsuba(string first, string second)
{

    padding(first, second);

    if (first.size() == 0)
        return "";

    if (first.size() == 1)
        return to_string((first.at(0) - '0') * (second.at(0) - '0'));

    const int left_half = first.size() / 2;                 //first half of integer  floor(n / 2)
    const int right_half = first.size() - first.size() / 2; //second half of

    string first_left = first.substr(0, left_half);
    string first_right = first.substr(left_half, right_half);

    string second_left = second.substr(0, left_half);
    string second_right = second.substr(left_half, right_half);

    string c2 = karatsuba(first_left, second_left);   //product of their first halves
    string c0 = karatsuba(first_right, second_right); //product of their second halves

    string t1 = str_addition(first_left, first_right);
    string t2 = str_addition(second_left, second_right);
    string c1 = karatsuba(t1, t2);
    c1 = str_subtraction(c1, str_addition(c0, c2));

    string result = str_right_shift(c2, right_half * 2);
    result = str_addition(result, str_right_shift(c1, right_half));
    result = str_addition(result, c0);

    //remove leading 0 in the string
    while (result.size() > 1 && result.front() == '0')
        result.erase(result.begin());

    return result;
}

int main()
{
    const int first_size = randint(1, 20);
    const int second_size = randint(1, 20);

    string first, second;
    for (int i = 0; i < first_size; i++)
        first.push_back('0' + randint(0, 9));

    for (int i = 0; i < second_size; i++)
        second.push_back('0' + randint(0, 9));

    //remove leading 0
    while (first.size() > 1 && first.front() == '0')
        first.erase(first.begin());
    while (second.size() > 1 && second.front() == '0')
        second.erase(second.begin());

    string res = karatsuba(first, second);

    //use 1 as threshold to prevent accuracy lose
    //not a great idea to test the result using
    //long double, may cause accuracy loss when the
    //number is too large, 
    if (stold(res) - stold(first) * stold(second) < 1)
        cout << "correct result" << endl;
    else
        cout << "wrong result" << endl;
}
