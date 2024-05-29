// without struct - working
#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <set>
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

int heuristics(vector<vector<int>> current, vector<vector<int>> goal)
{
    int h = 0;
    for (int i = 0; i < current.size(); i++)
    {
        for (int j = 0; j < current.size(); j++)
        {
            if (current[i][j] != 0 &&current[i][j] != goal[i][j])
            {
                h++;
            }
        }
    }
    return h;
}

void printBoard(vector<vector<int>> board)
{
    for (int i = 0; i < board.size(); i++)
    {
        for (int j = 0; j < board.size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

struct Comparator
{
    bool operator()(pair<int, vector<vector<int>>>n1, pair<int, vector<vector<int>>> n2 )
    {
        return (n1.first > n2.first);
    }
};

void solve(vector<vector<int>> &board, vector<vector<int>> &goal, int x, int y, int depth)
{
    // priority_queue<pair<int, vector<vector<int>>>, vector<pair<int, vector<vector<int>>>>,
    //                greater<pair<int, vector<vector<int>>>>>
    //     pq;
    priority_queue<pair<int, vector<vector<int>>>, vector<pair<int, vector<vector<int>>>>, Comparator> pq;
    set<vector<vector<int>>> visited;

    int statesExplored = 0;
    int count = 0;

    int h = heuristics(board, goal);
    pq.push({h, board});
    visited.insert(board);
    cout << "h : " << h << endl;
    printBoard(board);
    count++;

    while (!pq.empty())
    {

        vector<vector<int>> current = pq.top().second;
        pq.pop();
        statesExplored++;

        depth++;
        // printBoard(current);

        int x, y;
        findEmpty(current, x, y);
        if (current == goal)
        {
            cout << "Goal state reached" << endl;
            cout << "Depth: " << depth << endl;
            cout << "Cost: " << depth - 1 << endl;
            cout << "Visited: " << count << endl;
            cout << "Number of states explored: " << statesExplored << endl;

            return;
        }

        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};
        string moves[] = {"right", "left", "up", "down"};

        for (int i = 0; i < 4; i++)
        {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < current.size() && newY >= 0 && newY < current.size())
            {
                swap(current[x][y], current[newX][newY]);
                h = heuristics(current, goal);
                pq.push({h, current});
                cout << "h : " << h << endl;
                printBoard(current);
                count++;

                // if (visited.find(current) == visited.end())
                // {
                //     h = heuristics(current, goal);
                //     pq.push({h, current});
                //     visited.insert(current);
                //     cout << "h : " << h << endl;
                //     printBoard(current);
                //     count++;
                // }

                swap(current[newX][newY], current[x][y]);
            }
        }
    }
    cout << "No solution";
    return;
}

int main()
{
    vector<vector<int>> initial = {{2, 8, 3},
                                   {1, 6, 4},
                                   {7, 0, 5}};

    vector<vector<int>> goal = {{1, 2, 3},
                                {8, 0, 4},
                                {7, 6, 5}};

    int x, y;
    findEmpty(initial, x, y);
    solve(initial, goal, x, y, 0);
    return 0;
}
