#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
using namespace std;

using State = vector<vector<int>>;

bool isValid(State &state)
{
    int ml = state[0][0];
    int cl = state[0][1];
    int bl = state[0][2];

    int mr = state[1][0];
    int cr = state[1][1];
    int br = state[1][2];

    if (ml < 0 || cl < 0 || mr < 0 || cr < 0)
    {
        return false;
    }

    if (ml > 0 && ml < cl || mr > 0 && mr < cr)
    {
        return false;
    }
    return true;
}

vector<State> getSuccessor(State &state)
{
    vector<State> Successors;

    // boat is on left
    if (state[0][2] == 1)
    {
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 2; ++j)
            {
                if (i + j > 0 && i + j <= 2)
                {
                    State successor = {
                        {state[0][0] - i, state[0][1] - j, 0},
                        {state[1][0] + i, state[1][1] + j, 1}};

                    if (isValid(successor))
                    {
                        Successors.push_back(successor);
                    }
                }
            }
        }
    }

    else
    {
        for (int i = 0; i <= 2; ++i)
        {
            for (int j = 0; j <= 2; ++j)
            {
                if (i + j > 0 && i + j <= 2)
                {
                    State successor = {
                        {state[0][0] + i, state[0][1] + j, 1},
                        {state[1][0] - i, state[1][1] - j, 0}};

                    if (isValid(successor))
                    {
                        Successors.push_back(successor);
                    }
                }
            }
        }
    }

    return Successors;
}

bool dfs(State &current, State &goal, unordered_set<int> &visited, vector<State> &path)
{
    if (current == goal)
    {
        return true;
    }

    for (auto &successor : getSuccessor(current))
    {
        int hash = successor[0][0] * 10000 + successor[0][1] * 1000 + successor[0][2] * 100 + successor[1][0] * 10 + successor[1][1];

        if (visited.find(hash) == visited.end())
        {
            visited.insert(hash);
            path.push_back(successor);

            if (dfs(successor, goal, visited, path))
            {
                return true;
            }

            path.pop_back();
        }
    }

    return false;
}

void printSolution(vector<State> &solution)
{
    for (int i = 0; i < solution.size(); i++)
    {
        cout << "At depth " << i << ": Left Side ("
             << solution[i][0][0] << ", " << solution[i][0][1] << ", " << solution[i][0][2]
             << "), Right Side : ("
             << solution[i][1][0] << ", " << solution[i][1][1] << ", " << solution[i][1][2]
             << ")" << endl;
    }
}

int main()
{
    State initial = {{3, 3, 1}, {0, 0, 0}};
    State goal = {{0, 0, 0}, {3, 3, 1}};

    vector<State> path;
    unordered_set<int> visited;

    path.push_back(initial);
    int hash = initial[0][0] * 10000 + initial[0][1] * 1000 + 
    initial[0][2] * 100 + initial[1][0] * 10 + initial[1][1];

    visited.insert(hash);
    cout << "Using dfs :" << endl;

    if (dfs(initial, goal, visited,path))
    {
        printSolution(path);
    }
    else
    {
        cout << "No solution";
    }
    
    return 0;
}