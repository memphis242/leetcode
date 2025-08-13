#include <string>
#include <vector>
#include <unordered_map>
//#include <iostream>

using namespace std;

class Solution {
public:
    // I would declare these as const, but that would prevent usage of the []
    // operator to access elements, and force usage of the at() method, which
    // is ever so slightly slower in the case of guarantees that the key exists.
    static unordered_map<char, int> RomanNumToInt;
    static unordered_map<char, vector<char>> SpecialRomanChars;

    int romanToInt(string s) {
        int retval = 0;

        for ( size_t i = 0; i < s.length(); i++ ) {
            int increment;
            const char c = s[i];
            //MCMXCIV
            if ( auto it = SpecialRomanChars.find(c);
                    it != SpecialRomanChars.end() &&
                    i < (s.length() - 1) && (s[i+1] == it->second[0] || s[i+1] == it->second[1]) )
            {
                increment = RomanNumToInt[s[i+1]] - RomanNumToInt[c];
                ++i;
            }
            else
            {
                increment = RomanNumToInt[c];
            }
            retval += increment;
        }

        return retval;
    }
};

unordered_map<char, int> Solution::RomanNumToInt =
{
    { 'I', 1 },
    { 'V', 5 },
    { 'X', 10 },
    { 'L', 50 },
    { 'C', 100 },
    { 'D', 500 },
    { 'M', 1000 }
};

unordered_map<char, vector<char>> Solution::SpecialRomanChars =
{
    { 'I', { 'V', 'X' } },
    { 'X', { 'L', 'C' } },
    { 'C', { 'D', 'M' } }
};

//int main(void) {
//    Solution sol;
//    int res = sol.romanToInt("MCMXCIV");
//    cout << res << endl;
//}
