// #include <bits/stdc++.h>
// #include <iostream>
// #include <vector>
// #include <unordered_set>
// using namespace std;

// #define N 3
// struct Node
// {
//     Node *parent;
//     int board[N][N];
//     int x, y;
//     string action;
//     int depth;
// };

// void findEmpty(int board[N][N], int &x, int &y)
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             if (board[i][j] == 0)
//             {
//                 x = i;
//                 y = j;
//                 return;
//             }
//         }
//     }
// }

// Node *newNode(int board[N][N], int x, int y, int newX, int newY, string action, int depth, Node *parent)
// {
//     Node *node = new Node;
//     memcpy(node->board, board, sizeof(node->board));
//     node->x = newX;
//     node->y = newY;
//     swap(node->board[x][y], node->board[newX][newY]);
//     node->depth = depth;
//     node->action = action;
//     node->parent = parent;

//     return node;
// }
// bool isEqual(int mat1[N][N], int mat2[N][N])
// {
//     for (int i = 0; i < N; i++)
//         for (int j = 0; j < N; j++)
//             if (mat1[i][j] != mat2[i][j])
//                 return false;
//     return true;
// }

// void printBoard(int board[N][N])
// {
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             cout << board[i][j] << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }
// void printPath(Node *node)
// {
//     if (node == nullptr)
//         return;
//     printPath(node->parent);
//     if (!node->action.empty())
//     {
//         cout << "Move: " << node->action << endl;
//     }
//     printBoard(node->board);
// }

// bool dfs(Node *node, int goal[N][N], int depth)
// {
//     if (node == nullptr)
//     {
//         return true;
//     }
//     printPath(node->parent);
//     if (!node->action.empty())
//     {
//         cout << "Move: " << node->action << endl;
//     }
//     printBoard(node->board);
// }

// bool dfs(Node *node, int goal[N][N], unordered_set<string> &visited)
// {
//     if (isEqual(node->board, goal))
//     {
//         printPath(node);
//         return true;
//     }

//     string state;
//     for (int i = 0; i < N; i++)
//     {
//         for (int j = 0; j < N; j++)
//         {
//             state += to_string(node->board[i][j]);
//         }
//     }

//     if (visited.find(state) != visited.end())
//     {
//         return false;
//     }
//     visited.insert(state);

//     int dx[] = {0, 0, -1, 1};
//     int dy[] = {1, -1, 0, 0};
//     string moves[] = {"right", "left", "up", "down"};

//     for (int i = 0; i < 4; i++)
//     {
//         int newX = node->x + dx[i];
//         int newY = node->y + dy[i];

//         if (newX >= 0 && newX < N && newY >= 0 && newY < N)
//         {
//             Node *adj = newNode(node->board, node->x, node->y, newX, newY, moves[i], node->depth + 1, node);
//             if (dfs(adj, goal, visited))
//             {
//                 return true;
//             }
//             delete adj;
//         }
//     }
//     return false;
// }

// void solve(int board[N][N], int goal[N][N], int x, int y)
// {
//     unordered_set<string> visited;
//     Node *root = newNode(board, x, y, x, y, "", 0, nullptr);
//     if (!dfs(root, goal, visited))
//     {
//         cout << "NO solution";
//         return;
//     }
// }

// int main()
// {
//     int initial[N][N] = {{2, 8, 3},
//                          {1, 6, 4},
//                          {7, 0, 5}};

//     int goal[N][N] =
//         {{1, 2, 3},
//          {8, 0, 4},
//          {7, 6, 5}};

//     int x, y;
//     findEmpty(initial, x, y);
//     solve(initial, goal, x, y);
//     return 0;
// }

#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstring>

using namespace std;

#define N 3

struct Node {
    Node* parent;
    int board[N][N];
    int x, y;
    string action;
    int depth;
};

void findEmpty(int board[N][N], int& x, int& y) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) {
                x = i;
                y = j;
                return;
            }
        }
    }
}

Node* newNode(int board[N][N], int x, int y, int newX, int newY, string action, int depth, Node* parent) {
    Node* node = new Node;
    memcpy(node->board, board, sizeof(node->board));
    node->x = newX;
    node->y = newY;
    swap(node->board[x][y], node->board[newX][newY]);
    node->depth = depth;
    node->action = action;
    node->parent = parent;

    return node;
}

bool isEqual(int mat1[N][N], int mat2[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat1[i][j] != mat2[i][j])
                return false;
    return true;
}

void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printPath(Node* node) {
    if (node == nullptr)
        return;
    printPath(node->parent);
    if (!node->action.empty()) {
        cout << "Move: " << node->action << endl;
    }
    printBoard(node->board);
}

bool dfs(Node* node, int goal[N][N], unordered_set<string>& visited, int maxDepth) {
    if (node == nullptr || node->depth > maxDepth)
        return false;

    if (isEqual(node->board, goal)) {
        printPath(node);
        cout << "Depth: " << node->depth << endl;
        return true;
    }

    string state;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            state += to_string(node->board[i][j]);
        }
    }

    if (visited.find(state) != visited.end()) {
        return false;
    }
    visited.insert(state);

    int dx[] = {0, 0, -1, 1};
    int dy[] = {1, -1, 0, 0};
    string moves[] = {"right", "left", "up", "down"};

    for (int i = 0; i < 4; i++) {
        int newX = node->x + dx[i];
        int newY = node->y + dy[i];

        if (newX >= 0 && newX < N && newY >= 0 && newY < N) {
            Node* adj = newNode(node->board, node->x, node->y, newX, newY, moves[i], node->depth + 1, node);
            if (dfs(adj, goal, visited, maxDepth)) {
                // delete adj; // Free memory after exploring
                return true;
            }
            // delete adj;
        }
    }
    return false;
}

void solve(int board[N][N], int goal[N][N], int x, int y, int maxDepth) {
    unordered_set<string> visited;
    Node* root = newNode(board, x, y, x, y, "", 0, nullptr);
    if (!dfs(root, goal, visited, maxDepth)) {
        cout << "No solution within the specified depth limit." << endl;
    }
}

int main() {
    int initial[N][N] = {{2, 8, 3},
                         {1, 6, 4},
                         {7, 0, 5}};

    int goal[N][N] = {{1, 2, 3},
                      {8, 0, 4},
                      {7, 6, 5}};

    int x, y;
    findEmpty(initial, x, y);
    int maxDepth = 10; // Set maximum depth for DFS
    solve(initial, goal, x, y, maxDepth);
    return 0;
}
