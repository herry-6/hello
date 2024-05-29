// working with stack
#include <iostream>
#include <stack>
#include <map>
using namespace std;

void printSolution(map<pair<int, int>, pair<int, int>> mp, pair<int, int> u) {
    if (u.first == 0 && u.second == 0) {
        cout << 0 << " " << 0 << endl;
        return;
    }
    printSolution(mp, mp[u]);
    cout << u.first << " " << u.second << endl;
}

void solve(int a, int b, int target, int &count) {
    map<pair<int, int>, bool> visited;
    bool canSolve = false;
    map<pair<int, int>, pair<int, int>> mp;
    stack<pair<int, int>> s;

    s.push({0, 0});
    while (!s.empty()) {
        auto u = s.top();
        s.pop();

        if (visited[u] == true) {
            continue;
        }

        if (u.first > a || u.second > b || u.first < 0 || u.second < 0) {
            continue;
        }

        visited[{u.first, u.second}] = true;
        cout << u.first << " " << u.second << endl;
        count++;

        // if (u.first == target) // 2nd solution
        if (u.first == target || u.second == target) 
        {

            canSolve = true;
            cout << "Solved" << endl;
            printSolution(mp, u);
            if (u.first == target) {
                if (u.second != 0) {
                    cout << u.first << " " << 0 << endl;
                    count++;
                }
            } else {
                if(u.first != 0) {
                    cout << 0 << " " << u.second << endl;
                    count++;
                }
                cout << u.second << " " << 0 << endl;
                count++;
            }
            return;
        }

        
        if (visited[{a, u.second}] != true) {
            s.push({a, u.second});
            mp[{a, u.second}] = u;
        }

        if (visited[{u.first, b}] != true) {
            s.push({u.first, b});
            mp[{u.first, b}] = u;
        }

        if (visited[{0, u.second}] != true) {
            s.push({0, u.second});
            mp[{0, u.second}] = u;
        }

        if (visited[{u.first, 0}] != true) {
            s.push({u.first, 0});
            mp[{u.first, 0}] = u;
        }

        int x = b - u.second;
        if (u.first >= x) {
            int c = u.first - x;
            if (visited[{c, b}] != true) {
                s.push({c, b});
                mp[{c, b}] = u;
            }
        } else {
            int c = u.first + u.second;
            if (visited[{0, c}] != true) {
                s.push({0, c});
                mp[{0, c}] = u;
            }
        }

        x = a - u.first;
        if (u.second >= x) {
            int c = u.second - x;
            if (visited[{a, c}] != true) {
                s.push({a, c});
                mp[{a, c}] = u;
            }
        } else {
            int c = u.first + u.second;
            if (visited[{c, 0}] != true) {
                s.push({c, 0});
                mp[{c, 0}] = u;
            }
        }
    }
    if (!canSolve) {
        cout << "No solution";
    }
    return;
}

int main() {
    int a = 4;
    int b = 3;
    int target = 2;
    int count = 0;
    cout << "Water jug problem using DFS :" << endl;
    solve(a, b, target,count);
    cout << "Number of states visited :" << count ;

    return 0;
}
// #include <iostream>
// #include <stack>
// #include <map>
// using namespace std;

// void printSolution(map<pair<int, int>, pair<int, int>> mp, pair<int, int> u) {
//     if (u.first == 0 && u.second == 0) {
//         cout << 0 << " " << 0 << endl;
//         return;
//     }
//     printSolution(mp, mp[u]);
//     cout << u.first << " " << u.second << endl;
// }

// int solve(int a, int b, int target) {
//     map<pair<int, int>, bool> visited;
//     map<pair<int, int>, pair<int, int>> mp;
//     stack<pair<int, int>> s;

//     s.push({0, 0});
//     int depth = 0; // Initialize depth to 0
//     while (!s.empty()) {
//         auto u = s.top();
//         s.pop();

//         if (visited[u] == true) {
//             continue;
//         }

//         if (u.first > a || u.second > b || u.first < 0 || u.second < 0) {
//             continue;
//         }

//         visited[{u.first, u.second}] = true;

//         if (u.first == target || u.second == target) {
//             printSolution(mp, u);
//             if (u.first == target) {
//                 if (u.second != 0) {
//                     cout << u.first << " " << 0 << endl;
//                 }
//             } else {
//                 if(u.first != 0) {
//                     cout << 0 << " " << u.second << endl;
//                 }
//                 cout << u.second << " " << 0 << endl;
//             }
//             // Calculate depth by counting the number of steps taken
//             return depth;
//         }

//         // Increment depth for each step taken
//         depth++;

//         if (visited[{a, u.second}] != true) {
//             s.push({a, u.second});
//             mp[{a, u.second}] = u;
//         }

//         if (visited[{u.first, b}] != true) {
//             s.push({u.first, b});
//             mp[{u.first, b}] = u;
//         }

//         if (visited[{0, u.second}] != true) {
//             s.push({0, u.second});
//             mp[{0, u.second}] = u;
//         }

//         if (visited[{u.first, 0}] != true) {
//             s.push({u.first, 0});
//             mp[{u.first, 0}] = u;
//         }

//         int x = b - u.second;
//         if (u.first >= x) {
//             int c = u.first - x;
//             if (visited[{c, b}] != true) {
//                 s.push({c, b});
//                 mp[{c, b}] = u;
//             }
//         } else {
//             int c = u.first + u.second;
//             if (visited[{0, c}] != true) {
//                 s.push({0, c});
//                 mp[{0, c}] = u;
//             }
//         }

//         x = a - u.first;
//         if (u.second >= x) {
//             int c = u.second - x;
//             if (visited[{a, c}] != true) {
//                 s.push({a, c});
//                 mp[{a, c}] = u;
//             }
//         } else {
//             int c = u.first + u.second;
//             if (visited[{c, 0}] != true) {
//                 s.push({c, 0});
//                 mp[{c, 0}] = u;
//             }
//         }
//     }
//     // If no solution is found, return -1 to indicate failure
//     return -1;
// }

// int main() {
//     int a = 4;
//     int b = 3;
//     int target = 2;
//     cout << "Water jug problem using DFS :" << endl;
//     int depth = solve(a, b, target);
//     if (depth == -1) {
//         cout << "No solution";
//     } else {
//         cout << "Depth : " << depth << endl;
//     }
//     return 0;
// }
