#include <iostream>
#include <map>
using namespace std;

void printSolution(map<pair<int, int>, pair<int, int>> mp, pair<int, int> u)
{
    if (u.first == 0 && u.second == 0)
    {
        cout << 0 << " " << 0 << endl;
        return;
    }
    printSolution(mp, mp[u]);
    cout << u.first << " " << u.second << endl;
}

bool solveDLS(int a, int b, int target, int curj1, int curj2, map<pair<int, int>, bool> &visited, map<pair<int, int>, pair<int, int>> &mp, int depth, int maxDepth, int &count)
{
    if (depth > maxDepth)
    {
        return false; // Reached depth limit
    }

    if (curj1 > a || curj2 > b || curj1 < 0 || curj2 < 0)
    {
        return false;
    }

    if (visited[{curj1, curj2}])
    {
        return false;
    }

    visited[{curj1, curj2}] = true;
    cout << curj1 << " " << curj2 << endl;
    count++;

    if (curj1 == target || curj2 == target)
    {
        cout << "Solved" << endl;
        printSolution(mp, {curj1, curj2});
        if (curj1 == target)
        {
            if (curj2 != 0)
            {
                cout << curj1 << " " << 0 << endl;
                count++;
            }
        }
        else
        {
            if (curj1 != 0)
            {
                cout << 0 << " " << curj2 << endl;
                count++;
            }
            cout << curj2 << " " << 0 << endl;
            count++;
        }
        return true;
    }

    // Fill jug1
    if (!visited[{a, curj2}])
    {
        mp[{a, curj2}] = {curj1, curj2};
        if (solveDLS(a, b, target, a, curj2, visited, mp, depth + 1, maxDepth, count))
        {
            return true;
        }
    }

    // Fill jug2
    if (!visited[{curj1, b}])
    {
        mp[{curj1, b}] = {curj1, curj2};
        if (solveDLS(a, b, target, curj1, b, visited, mp, depth + 1, maxDepth, count))
        {
            return true;
        }
    }

    // Empty jug1
    if (!visited[{0, curj2}])
    {
        mp[{0, curj2}] = {curj1, curj2};
        if (solveDLS(a, b, target, 0, curj2, visited, mp, depth + 1, maxDepth, count))
        {
            return true;
        }
    }

    // Empty jug2
    if (!visited[{curj1, 0}])
    {
        mp[{curj1, 0}] = {curj1, curj2};
        if (solveDLS(a, b, target, curj1, 0, visited, mp, depth + 1, maxDepth, count))
        {
            return true;
        }
    }

    // Transfer from jug1 to jug2
    int x = b - curj2;
    if (curj1 >= x)
    {
        int c = curj1 - x;
        if (!visited[{c, b}])
        {
            mp[{c, b}] = {curj1, curj2};
            if (solveDLS(a, b, target, c, b, visited, mp, depth + 1, maxDepth, count))
            {
                return true;
            }
        }
    }
    else
    {
        int c = curj1 + curj2;
        if (!visited[{0, c}])
        {
            mp[{0, c}] = {curj1, curj2};
            if (solveDLS(a, b, target, 0, c, visited, mp, depth + 1, maxDepth, count))
            {
                return true;
            }
        }
    }

    // Transfer from jug2 to jug1
    x = a - curj1;
    if (curj2 >= x)
    {
        int c = curj2 - x;
        if (!visited[{a, c}])
        {
            mp[{a, c}] = {curj1, curj2};
            if (solveDLS(a, b, target, a, c, visited, mp, depth + 1, maxDepth, count))
            {
                return true;
            }
        }
    }
    else
    {
        int c = curj1 + curj2;
        if (!visited[{c, 0}])
        {
            mp[{c, 0}] = {curj1, curj2};
            if (solveDLS(a, b, target, c, 0, visited, mp, depth + 1, maxDepth, count))
            {
                return true;
            }
        }
    }

    return false;
}

bool solveIDDFS(int a, int b, int target, map<pair<int, int>, bool> &visited, map<pair<int, int>, pair<int, int>> &mp, int maxDepth, int &count)
{
    for (int depth = 0; depth <= maxDepth; depth++)
    {
        if (solveDLS(a, b, target, 0, 0, visited, mp, 0, depth, count))
        {
            return true; // Solution found
        }
        // Reset visited and mp for next iteration
        visited.clear();
        mp.clear();
    }
    return false; // Solution not found within max depth
}

int main()
{
    int a = 4;
    int b = 3;
    int target = 2;
    int maxDepth = 10;
    int count = 0;
    map<pair<int, int>, bool> visited;
    map<pair<int, int>, pair<int, int>> mp;
    cout << "Water jug problem using Iterative Deepening Depth First Search (IDDFS):" << endl;
    bool res = solveIDDFS(a, b, target, visited, mp, maxDepth, count);
    if (!res)
    {
        cout << "No solution" << endl;
    }
    cout << "Number of states visited: " << count << endl;
    return 0;
}
