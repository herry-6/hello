#include <bits/stdc++.h>
#include <vector>
using namespace std;

void findEmpty(vector<vector<int>> &board, int &x, int &y)
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

vector<pair<vector<vector<int>>, string>> findAdj(vector<vector<int>> &state)
{
    vector<pair<vector<vector<int>>, string>> neighbours;
    int x = -1, y = -1;

    findEmpty(state, x, y);

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};
    string moves[] = {"right", "left", "up", "down"};

    for (int i = 0; i < 4; i++)
    {
        int newX = x + dx[i];
        int newY = y + dy[i];

        if (newX >= 0 && newX < state.size() && newY >= 0 && newY < state.size())
        {
            vector<vector<int>> neighbourState = state;
            swap(neighbourState[x][y], neighbourState[newX][newY]);
            neighbours.push_back(make_pair(neighbourState, moves[i]));
        }
    }

    return neighbours;
}

vector<pair<vector<vector<int>>, string>> bfs(vector<vector<int>> &initial, vector<vector<int>> &goal)
{
    unordered_set<string> visited;
    queue<vector<vector<int>>> q;
    int count = 0;

    queue<vector<pair<vector<vector<int>>, string>>> paths;

    q.push(initial);
    paths.push({});

    while (!q.empty())
    {
        auto current = q.front();
        q.pop();

        auto path = paths.front();
        paths.pop();

        if (current == goal)
        {
            cout << "Number of stated visited : " << count << endl;
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
        count++;

        for (auto neighbourPair : findAdj(current))
        {
            auto neighbour = neighbourPair.first;
            auto move = neighbourPair.second;

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
                q.push(neighbour);
                auto newPath = path;
                newPath.push_back(make_pair(neighbour, move));
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

    // vector<vector<int>> initial = {{1, 2, 3},
    //                                {8, 0, 4},
    //                                {7, 6, 5}};

    // vector<vector<int>> goal = {{2, 8, 1},
    //                             {0, 4, 3},
    //                             {7, 6, 5}};

    vector<pair<vector<vector<int>>, string>> result = bfs(initial, goal);
    // vector<pair<vector<vector<int>>, string>> solution = result.first;
    // int statesExplored = result.second;

    if (!result.empty())
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
        for (auto stateActionPair : result)
        {
            auto state = stateActionPair.first;
            auto action = stateActionPair.second;
            cout << "Action: " << action << endl;
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

    return 0;
}
