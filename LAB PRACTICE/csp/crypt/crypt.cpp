// single solution
// only 1 valid solution
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <set>
using namespace std;

int evaluateTerm(const string &term, const unordered_map<char, int> &mp)
{
    int value = 0;
    for (char ch : term)
    {
        value = value * 10 + mp.at(ch);
    }
    return value;
}

bool backtrack(int i, const set<char> &uniqueLetters, unordered_map<char, int> &mp, vector<bool> &used, const vector<string> &words, const string &result)
{
    // cout << i << endl;
    if (i == uniqueLetters.size())
    {
        int value1 = evaluateTerm(words[0], mp);
        int value2 = evaluateTerm(words[1], mp);
        int value3 = evaluateTerm(result, mp);
        return value1 + value2 == value3;
    }

    char currentLetter = *next(uniqueLetters.begin(), i);
    for (int digit = 0; digit <= 9; digit++)
    {
        if (!used[digit])
        {
            mp[currentLetter] = digit;
            used[digit] = true;
            if (backtrack(i + 1, uniqueLetters, mp, used, words, result))
            {
                return true;
            }
            used[digit] = false;
            mp[currentLetter] = -1; // Reset the assignment
        }
    }
    return false;
}

void solve(const vector<string> &words, const string &result)
{
    unordered_map<char, int> mp;
    set<char> uniqueLetters;
    for (const string &s : words)
    {
        for (char ch : s)
        {
            if (isalpha(ch) && uniqueLetters.find(ch) == uniqueLetters.end())
            {
                uniqueLetters.insert(ch);
            }
        }
    }
    for (char ch : result)
    {
        if (isalpha(ch) && uniqueLetters.find(ch) == uniqueLetters.end())
        {
            uniqueLetters.insert(ch);
        }
    }

    vector<bool> used(10, false); // Indicates if a digit is used
    if (backtrack(0, uniqueLetters, mp, used, words, result))
    {
        cout << "Solution found:" << endl;
        for (char letter : uniqueLetters)
        {
            cout << letter << " = " << mp[letter] << endl;
        }
    }
    else
    {
        cout << "No solution found." << endl;
    }
}

int main()
{

    string s1, s2, result;
    cout << "Enter string 1 : ";
    cin >> s1;
    cout << "Enter string 2 : ";
    cin >> s2;
    cout << "Enter result string : ";
    cin >> result;

    vector<string> words = {s1, s2};

    solve(words, result);
    return 0;
}
