#include <bits/stdc++.h>
#include <vector>
using namespace std;


printSolution(vector<vector<int>> &board)
{
    int n = board.size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            if (board[i][j] == 1)
            {
                cout << "Q" << i << "\t";
            }
            else
            {
                cout << board[i][j] << "\t";
            }

        cout << endl;
    }
    cout << endl;

    // vector<int> ans(n, 0);
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         if (board[i][j] == 1)
    //         {
    //             ans[i] = j+1;
    //         }
    //     }
    // }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << ans[i] << " ";
    // }
}

bool isSafe(vector<vector<int>> &board, int row, int col)
{
    int n = board.size();

    // check for row
    for (int j = 0; j < col; j++)
    {
        if (board[row][j] == 1)
        {
            return false; 
        }
    }
    // check for upper left
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
    // check for lower left
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 1)
        {
            return false;
        }
    }
}

void solveQueens(vector<vector<int>> &board, int col, int &count)
{
    int n = board.size();

    if (col >= n)
    {
       return;
    }

    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;

           if (col == n - 1)
           {
                cout << "Solution " << count+1 << endl;
                printSolution(board);
                count++;
           }
            solveQueens(board, col + 1, count);
            board[i][col] = 0;
        }
    }
}

int main()
{
    int n;
    cout << "Enter the number of queens : ";
    cin >> n;
    int count  = 0;
    vector<vector<int>> board(n, vector<int>(n, 0));
    solveQueens(board,0, count);
    if (count == 0)
    {
        cout << "No solution";
    }
    

    return 0;
}