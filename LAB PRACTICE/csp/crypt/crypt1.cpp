// multiple solutions
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
#include <set>

using namespace std;

int evaluateTerm(const string &term, const unordered_map<char, int> &mp) {
    int value = 0;
    for (char ch : term) {
        value = value * 10 + mp.at(ch);
    }
    return value;
}

bool backtrack(int i, const set<char> &uniqueLetters, unordered_map<char, int> &mp, vector<bool> &used, const vector<string> &words, const string &result, vector<unordered_map<char, int>> &solutions) {
    if (i == uniqueLetters.size()) {
        int value1 = evaluateTerm(words[0], mp);
        int value2 = evaluateTerm(words[1], mp);
        int value3 = evaluateTerm(result, mp);
        if (value1 + value2 == value3) {
            solutions.push_back(mp);
            return false;  // Continue searching for other solutions
        }
        return false;
    }

    char currentLetter = *next(uniqueLetters.begin(), i);
    for (int digit = 0; digit <= 9; digit++) {
        if (!used[digit]) {
            mp[currentLetter] = digit;
            used[digit] = true;
            backtrack(i + 1, uniqueLetters, mp, used, words, result, solutions);
            used[digit] = false;
            mp[currentLetter] = -1; // Reset the assignment
        }
    }
    return false;
}

void solve(const vector<string> &words, const string &result) {
    unordered_map<char, int> mp;
    set<char> uniqueLetters;
    for (const string &s : words) {
        for (char ch : s) {
            if (isalpha(ch)) {
                uniqueLetters.insert(ch);
            }
        }
    }
    for (char ch : result) {
        if (isalpha(ch)) {
            uniqueLetters.insert(ch);
        }
    }

    vector<bool> used(10, false); // Indicates if a digit is used
    vector<unordered_map<char, int>> solutions;

    backtrack(0, uniqueLetters, mp, used, words, result, solutions);

    if (!solutions.empty()) {
        cout << "Number of solutions : " << solutions.size() << endl;
        cout << "Solutions found:" << endl;
        for (const auto &solution : solutions) {
            for (char letter : uniqueLetters) {
                cout << letter << " = " << solution.at(letter) << ", ";
            }
            cout << endl;
        }
    } else {
        cout << "No solution found." << endl;
    }
}

int main() {
    string s1, s2, result;
    cout << "Enter string 1: ";
    cin >> s1;
    cout << "Enter string 2: ";
    cin >> s2;
    cout << "Enter result string: ";
    cin >> result;

    vector<string> words = {s1, s2};

    solve(words, result);
    return 0;
}
