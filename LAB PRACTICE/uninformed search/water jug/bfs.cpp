// working
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <queue>
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

void bfs(int a, int b, int target, int &count)
{
    map<pair<int, int>, bool> visited;
    bool canSolve = false;
    map<pair<int, int>, pair<int, int>> mp;
    queue<pair<int, int>> q;

    q.push({0, 0});
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();

        if (visited[u] == true)
        {
            continue;
        }

        if (u.first > a || u.second > b || u.first < 0 || u.second < 0)
        {
            continue;
        }

        visited[{u.first, u.second}] = true;
        cout << u.first << " " << u.second << endl;
        count++;

        // if (u.first == target) // 2nd solution
        if (u.first == target || u.second == target)
        {
            canSolve = true;
            cout << "Solved"<< endl;
            printSolution(mp, u);
            if (u.first == target)
            {
                if (u.second != 0)
                {
                    cout << u.first << " " << 0 << endl;
                    count++;
                }
            }
            else
            {
                if (u.first != 0)
                {
                    cout << 0 << " " << u.second << endl;
                    count++;
                }
                cout << u.second << " " << 0 << endl;
                    count++;

            }
            return;
        }

        // fill jug a
        if (visited[{a, u.second}] != true)
        {
            q.push({a, u.second});
            mp[{a, u.second}] = u;
        }
        // fill jug b
        if (visited[{u.first, b}] != true)
        {
            q.push({u.first, b});
            mp[{u.first, b}] = u;
        }
        // empty a
        if (visited[{0, u.second}] != true)
        {
            q.push({0, u.second});
            mp[{0, u.second}] = u;
        }
        // empty b
        if (visited[{u.first, 0}] != true)
        {
            q.push({u.first, 0});
            mp[{u.first, 0}] = u;
        }
        // transfer a to b
        int x = b - u.second;
        if (u.first > x)
        {
            int c = u.first - x;
            if (visited[{c, b}] != true)
            {
                q.push({c, b});
                mp[{c, b}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (visited[{0, c}] != true)
            {
                q.push({0, c});
                mp[{0, c}] = u;
            }
        }

        // tranfer b to a
        x = a - u.first;
        if (u.second >= x)
        {
            int c = u.second - x;
            if (visited[{a, c}] != true)
            {
                q.push({a, c});
                mp[{a, c}] = u;
            }
        }
        else
        {
            int c = u.first + u.second;
            if (visited[{c, 0}] != true)
            {
                q.push({c, 0});
                mp[{c, 0}] = u;
            }
        }
    }
    if (!canSolve)
    {
        cout << "No solution";
    }
}
int main()
{
    int a = 4;
    int b = 3;
    int target = 2;
    int count =0;
    cout << "Water jug problem using BFS :" << endl;
    bfs(a, b, target, count);
    cout << "Number of states visited :" << count ;
    return 0;
}

// #include <bits/stdc++.h>
// #include <vector>
// #include <map>
// #include <queue>
// using namespace std;

// void printSolution(map<pair<int, int>, pair<int, int>> mp, pair<int, int> u)
// {
//     if (u.first == 0 && u.second == 0)
//     {
//         cout << 0 << " " << 0 << endl;
//         return;
//     }
//     printSolution(mp, mp[u]);
//     cout << u.first << " " << u.second << endl;
// }

// void bfs(int a, int b, int target, int &count, int &depth)
// {
//     map<pair<int, int>, bool> visited;
//     bool canSolve = false;
//     map<pair<int, int>, pair<int, int>> mp;
//     queue<pair<pair<int, int>, int>> q; // Modified queue to include depth

//     q.push({{0, 0}, 0}); // Initial state with depth 0
//     while (!q.empty())
//     {
//         auto front = q.front();
//         auto u = front.first;
//         int currentDepth = front.second; // Extract depth
//         q.pop();

//         if (visited[u] == true)
//         {
//             continue;
//         }

//         if (u.first > a || u.second > b || u.first < 0 || u.second < 0)
//         {
//             continue;
//         }

//         visited[{u.first, u.second}] = true;
//         count++;

//         // Update depth
//         depth = max(depth, currentDepth);

//         if (u.first == target || u.second == target)
//         {
//             canSolve = true;

//             printSolution(mp, u);
//             if (u.first == target)
//             {
//                 if (u.second != 0)
//                 {
//                     cout << u.first << " " << 0 << endl;
//                     count++;
//                 }
//             }
//             else
//             {
//                 if (u.first != 0)
//                 {
//                     cout << 0 << " " << u.second << endl;
//                     count++;
//                 }
//                 cout << u.second << " " << 0 << endl;
//                 count++;
//             }
//             return;
//         }

//         if (visited[{a, u.second}] != true)
//         {
//             q.push({{a, u.second}, currentDepth + 1}); // Update depth
//             mp[{a, u.second}] = u;
//         }

//         if (visited[{u.first, b}] != true)
//         {
//             q.push({{u.first, b}, currentDepth + 1}); // Update depth
//             mp[{u.first, b}] = u;
//         }

//         if (visited[{0, u.second}] != true)
//         {
//             q.push({{0, u.second}, currentDepth + 1}); // Update depth
//             mp[{0, u.second}] = u;
//         }

//         if (visited[{u.first, 0}] != true)
//         {
//             q.push({{u.first, 0}, currentDepth + 1}); // Update depth
//             mp[{u.first, 0}] = u;
//         }

//         int x = b - u.second;
//         if (u.first > x)
//         {
//             int c = u.first - x;
//             if (visited[{c, b}] != true)
//             {
//                 q.push({{c, b}, currentDepth + 1}); // Update depth
//                 mp[{c, b}] = u;
//             }
//         }
//         else
//         {
//             int c = u.first + u.second;
//             if (visited[{0, c}] != true)
//             {
//                 q.push({{0, c}, currentDepth + 1}); // Update depth
//                 mp[{0, c}] = u;
//             }
//         }

//         x = a - u.first;
//         if (u.second >= x)
//         {
//             int c = u.second - x;
//             if (visited[{a, c}] != true)
//             {
//                 q.push({{a, c}, currentDepth + 1}); // Update depth
//                 mp[{a, c}] = u;
//             }
//         }
//         else
//         {
//             int c = u.first + u.second;
//             if (visited[{c, 0}] != true)
//             {
//                 q.push({{c, 0}, currentDepth + 1}); // Update depth
//                 mp[{c, 0}] = u;
//             }
//         }
//     }
//     if (!canSolve)
//     {
//         cout << "No solution";
//     }
// }

// int main()
// {
//     int a = 4;
//     int b = 3;
//     int target = 2;
//     int count = 0;
//     int depth = 0;
//     cout << "Water jug problem using BFS :" << endl;
//     bfs(a, b, target, count, depth);
//     cout << "Number of states visited: " << count << endl;
//     cout << "Depth of the state space tree: " << depth << endl;
//     return 0;
// }
