#include <bits/stdc++.h>
#include <vector>
using namespace std;

printSolution(vector<vector<int>> &board)
{
    int n = board.size();

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //         if (board[i][j] == 1)
    //         {
    //             cout << "Q" << i << "\t";
    //         }
    //         else
    //         {
    //             cout << board[i][j] << "\t";
    //         }

    //     cout << endl;
    // }
    // cout << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) {
                cout << "Q" << i << "\t";
            } else if (board[i][j] == -1) {
                cout << "X" << " "; // Mark the position being checked as 'X'
            } else {
                cout << board[i][j] << "\t";
            }
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
            // cout << "Not safe at (" << row << ", " << col << "):" << endl;
            // printSolution(board);

             // Print the board when a position is not safe
            cout << "Position (" << row << ", " << col << ") is not safe because of row conflict with (" << row << ", " << j << "):" << endl;
            board[row][col] = -1; // Temporarily mark the position
            printSolution(board);
            board[row][col] = 0; // Unmark the position
            return false; 
        }
    }
    // check for upper left
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j] == 1)
        {
            // cout << "Not safe at (" << row << ", " << col << "):" << endl;
            // printSolution(board);
            // Print the board when a position is not safe
            cout << "Position (" << row << ", " << col << ") is not safe because of upper left diagonal conflict with (" << i << ", " << j << "):" << endl;
            board[row][col] = -1; // Temporarily mark the position
            printSolution(board);
            board[row][col] = 0; // Unmark the position
            return false;
        }
    }
    // check for lower left
    for (int i = row, j = col; i < n && j >= 0; i++, j--)
    {
        if (board[i][j] == 1)
        {
            // cout << "Not safe at (" << row << ", " << col << "):" << endl;
            // printSolution(board);
            // Print the board when a position is not safe
            cout << "Position (" << row << ", " << col << ") is not safe because of lower left diagonal conflict with (" << i << ", " << j << "):" << endl;
            board[row][col] = -1; // Temporarily mark the position
            printSolution(board);
            board[row][col] = 0; // Unmark the position
            return false;
        }
    }
}

bool solveQueens(vector<vector<int>> &board, int col)
{
    int n = board.size();

    if (col >= n)
    {
        cout << "Final result : " << endl;
        printSolution(board);
        return true;
    }

    for (int i = 0; i < n; i++)
    {
        if (isSafe(board, i, col))
        {
            board[i][col] = 1;

            cout << "Trying to place queen at (" << i << ", " << col << "):" << endl;
            printSolution(board);

            if (solveQueens(board, col + 1))
            {
                return true;
            }

            cout << "Backtracking from (" << i << ", " << col << "):" << endl;
            printSolution(board);
            board[i][col] = 0;
        }
    }
    return false;
}

int main()
{
    int n;
    cout << "Enter the number of queens : ";
    cin >> n;
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (!solveQueens(board, 0))
    {
        cout << "No solution";
    }

    return 0;
}