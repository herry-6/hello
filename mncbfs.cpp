#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <queue>
using namespace std;

using State = vector<vector<int>>;

// check valid state or not
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

vector<State> getsuccessor(State &state)
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

vector<State> bfs(State &intial, State &goal)
{
    if (!isValid(intial))
    {
        return {};
    }

    unordered_set<int> visited;
    queue<vector<State>> q;
    q.push({intial});

    while (!q.empty())
    {
        vector<State> path = q.front();
        q.pop();
        State currentState = path.back();

        int hash = currentState[0][0] * 10000 + currentState[0][1] * 1000 + currentState[0][2] * 100 + currentState[1][0] * 10 + currentState[1][1];

        if (visited.find(hash) != visited.end())
        {
            continue;
        }

        visited.insert(hash);

        if (currentState == goal)
        {
            return path;
        }

        for (auto &successor : getsuccessor(currentState))
        {
            vector<State> newPath = path;
            newPath.push_back(successor);
            q.push(newPath);
        }
    }

    return {};
}
// void printState(State &state)
// {
//     cout << "Left Side: (";
//     for (int i = 0; i < state[0][0]; ++i) cout << "M";
//     cout << ",";
//     for (int i = 0; i < state[0][1]; ++i) cout << "C";
//     cout << ", " << (state[0][2] == 1 ? "Boat" : "No Boat") << ") ";

//     cout << "Right Side: (";
//     for (int i = 0; i < state[1][0]; ++i) cout << "M";
//     cout << ",";
//     for (int i = 0; i < state[1][1]; ++i) cout << "C";
//     cout << ", " << (state[1][2] == 1 ? "Boat" : "No Boat") << ")";
// }

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


    //  for (int i = 0; i < solution.size(); i++)
    // {
    //     cout << "At depth " << i << ": ";
    //     printState(solution[i]);
    //     cout << endl;
    // }
    
}

int main()
{

    State initial = {{3, 3, 1}, {0, 0, 0}};
    State goal = {{0, 0, 0}, {3, 3, 1}};

    vector<State> solution = bfs(initial, goal);
    cout << "Using bfs" << endl;
    if (solution.empty())
    {
        cout << "No solution";
    }
    else
    {
        printSolution(solution);
    }
    

    return 0;
}