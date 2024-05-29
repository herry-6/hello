#include <bits/stdc++.h>
#include <vector>
#include <unordered_set>
#include <stack>
#include <cstring>
using namespace std;

void findEmpty(vector<vector<int>> board, int &x, int &y)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 0)
            {
                x = i;
                y = j;
                return;
            }
        }
    }
}

vector<vector<vector<int>>> findAdj(vector<vector<int>> &state)
{
    vector<vector<vector<int>>> neighbours;
    int x = -1;
    int y = -1;

    findEmpty(state, x, y);

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < state.size() && newY >= 0 && newY < state.size())
        {
            vector<vector<int>> neighbourState = state;
            swap(neighbourState[x][y], neighbourState[newX][newY]);
            neighbours.push_back(neighbourState);
        }
    }

    return neighbours;
}

vector<vector<vector<int>>> dfs(vector<vector<int>> &initial, vector<vector<int>> &goal, int &statesExplored)
{
    unordered_set<string> visited;
    stack<vector<vector<int>>> s;
    s.push(initial);

    stack<vector<vector<vector<int>>>> paths;
    paths.push({});

    while (!s.empty())
    {
        auto current = s.top();
        s.pop();

        auto path = paths.top();
        paths.pop();

        statesExplored++;  // Increment the counter for each state processed

        if (current == goal)
        {
            return path;
        }

        string vis = "";
        for (auto &row : current)
        {
            for (int num : row)
            {
                vis += to_string(num);
            }
        }

        if (visited.find(vis) != visited.end())
        {
            continue;
        }

        visited.insert(vis);

        for (auto neighbour : findAdj(current))
        {
            string neigh = "";
            for (auto &row : neighbour)
            {
                for (int num : row)
                {
                    neigh += to_string(num);
                }
            }

            if (visited.find(neigh) == visited.end())
            {
                s.push(neighbour);
                auto newPath = path;
                newPath.push_back(neighbour);
                paths.push(newPath);
            }
        }
    }

    return {};
}

int main()
{
    vector<vector<int>> initial = {{2, 8, 3},
                                   {1, 6, 4},
                                   {7, 0, 5}};

    vector<vector<int>> goal = {{1, 2, 3},
                                {8, 0, 4},
                                {7, 6, 5}};

    int statesExplored = 0;
    vector<vector<vector<int>>> solution = dfs(initial, goal, statesExplored);


    if (!solution.empty())
    {
        cout << "Solution found:" << endl;
        for (auto &row : initial)
        {
            for (auto &num : row)
            {
                cout << num << " ";
            }
            cout << endl;
        }
        cout << endl;
        for (auto &state : solution)
        {
            for (auto &row : state)
            {
                for (int num : row)
                {
                    cout << num << " ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }
    else
    {
        cout << "No solution found." << endl;
    }

    cout << "Number of states explored: " << statesExplored << endl;

    return 0;
}
