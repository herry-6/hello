// new with struct - working
#include<bits/stdc++.h>
#include <cstring>
#include <iostream>
#include<vector>
#include <algorithm>
#include <queue>
using namespace std;

#define N 3

struct Node
{
    Node* parent;
    int board[N][N];
    int depth;
    int h;
    int x, y;
    string action;
};

void findEmpty(int board[N][N], int &x, int &y)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
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

int heuristics(int current[N][N], int goal[N][N])
{
    int h = 0;
    for (int i = 0; i <N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (current[i][j] != 0 && current[i][j] != goal[i][j])
            {
                h++;
            }
        }
    }
    return h;
}

bool isGoalState(int board[N][N], int goal[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] != goal[i][j])
                return false;
        }
    }
    return true;
}

void printBoard(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void printPath(Node *node)
{
    if (node == nullptr)
        return;
    printPath(node->parent);
    if (!node->action.empty())
    {
        cout << "Move: " << node->action << endl;
    }
    printBoard(node->board);
}

Node *newNode(int board[N][N], int x, int y, int newX, int newY, int depth, Node* parent, string action)
{
    Node * node = new Node;
    memcpy(node->board, board, sizeof(node->board));
    node->x = newX;
    node->y = newY;
    swap(node->board[x][y], node->board[newX][newY]);
    node->depth = depth;
    node->parent = parent;
    node->action = action;

    return node;

}

struct Comparator
{
    bool operator()(Node *n1, Node *n2)
    {
        return (n1->h > n2->h);
    }
};


void solve(int board[N][N], int goal[N][N], int x, int y)
{

    priority_queue<Node*, vector<Node*>, Comparator>
        pq;

    int statesExplored = 0;
    int count = 0;

    Node* root = newNode(board, x,y,x,y,0,nullptr,"");
    root->h = heuristics(board, goal);

    pq.push(root);

    cout << "h : " << root->h << endl;
    printBoard(board);
    count++;

    while (!pq.empty())
    {

        Node *current = pq.top();
        pq.pop();
        statesExplored++;

        cout << "Expanding node : " << endl;
        printBoard(current->board);

        findEmpty(current->board, x, y);
        
        if (isGoalState(current->board, goal))
        {
            cout << "Goal state reached" << endl;
            printPath(current);
            cout << "Depth: " << current->depth << endl;
            cout << "Cost: " << current->depth -1 << endl;
            cout << "Visited: " << count << endl;
            cout << "Number of states explored: " << statesExplored << endl;

            return;
        }

        int dx[] = {0, 0, -1, 1};
        int dy[] = {1, -1, 0, 0};
        string moves[] = {"right", "left", "up", "down"};

        for (int i = 0; i < 4; i++)
        {
            int newX = current->x + dx[i];
            int newY = current->y + dy[i];

            if (newX >= 0 && newX < N && newY >= 0 && newY < N)
            {
                Node *adj = newNode(current->board, current->x, current->y, newX, newY, current->depth+1, current, moves[i]);
                adj->h =  heuristics(adj->board, goal);
                pq.push(adj);

                cout << "h : " << adj->h << endl;
                printBoard(current->board);
                count++;
            }
        }
    }
    cout << "No solution";
    return;
}
int main()
{
     int initial[N][N] = {{2, 8, 3},
                         {1, 6, 4},
                         {7, 0, 5}};

    int goal[N][N] = {{1, 2, 3},
                      {8, 0, 4},
                      {7, 6, 5}};

    int x,y;
    findEmpty(initial,x,y);
    solve(initial, goal, x,y);
    return 0;
}