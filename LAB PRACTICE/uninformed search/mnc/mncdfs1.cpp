#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
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

void printState(State &state)
{
    cout << "Left Side: (" << state[0][0] << ", " << state[0][1] << ", " << state[0][2] << "), ";
    cout << "Right Side: (" << state[1][0] << ", " << state[1][1] << ", " << state[1][2] << ")" << endl;
}

void printOpenClosedLists(stack<vector<State>> &open, unordered_set<int> &closed)
{
    cout << "Open List:" << endl;
    stack<vector<State>> temp = open;
    while (!temp.empty())
    {
        vector<State> path = temp.top();
        temp.pop();
        printState(path.back());
    }
    cout << "Closed List:" << endl;
    for (int state_hash : closed)
    {
        State state = {
            {state_hash / 10000, (state_hash / 1000) % 10, (state_hash / 100) % 10},
            {(state_hash / 10) % 10, state_hash % 10, 1}};
        printState(state);
    }
}

vector<State> dfs(State &initial, State &goal)
{
    if (!isValid(initial))
    {
        return {};
    }

    unordered_set<int> visited;
    stack<vector<State>> open;
    open.push({initial});

    while (!open.empty())
    {
        vector<State> path = open.top();
        open.pop();
        State currentState = path.back();

        int hash = currentState[0][0] * 10000 + currentState[0][1] * 1000 + currentState[0][2] * 100 + currentState[1][0] * 10 + currentState[1][1];

        visited.insert(hash);

        if (currentState == goal)
        {
            return path;
        }

        for (auto &successor : getsuccessor(currentState))
        {
            int successor_hash = successor[0][0] * 10000 + successor[0][1] * 1000 + successor[0][2] * 100 + successor[1][0] * 10 + successor[1][1];
            if (visited.find(successor_hash) == visited.end())
            {
                vector<State> newPath = path;
                newPath.push_back(successor);
                open.push(newPath);
            }
        }

        printOpenClosedLists(open, visited);
    }

    return {};
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

    vector<State> solution = dfs(initial, goal);
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
