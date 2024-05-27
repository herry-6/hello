#include <bits/stdc++.h>
#include <vector>
using namespace std;

int turn;
int board[10] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

// X(1) odd turn = 3;
// O(0) even turn = 5;

void GO(int n)
{
    if (turn % 2 == 0)
    {
        board[n] = 5;
    }
    else
    {
        board[n] = 3;
    }
    cout << "Placing at " << n << endl;
    turn++;
}

int Make2()
{
    if (board[5] == 2)
    {
        return 5;
    }
    int x = 5;
    int arr[] = {2,4,6,8};
    while (x != 2)
    {
        x = rand() % 4;
    }
    cout << "randon no : " << arr[x] << endl;
    return arr[x];
}

int findBlank()
{
  for(int i = 1; i<=9; i++)
  {
    if(board[i] == 2)
    {
      return i;
    }
  }
  return -1;
}


void printBoard()
{
    cout << "-------------" << endl;
    cout <<"| ";
    for (int i = 1; i <= 3; i++)
    {
        
        if (board[i] == 5)
        {
            cout << "5" << " ";
            cout <<"| ";
        }
        else if (board[i] == 3)
        {
            cout << "3" << " ";
            cout <<"| ";
        }
        else
        {
            cout << board[i] << " ";
            cout <<"| ";
        }
        
    }
    cout << endl;
    cout << "-------------" << endl;
    cout <<"| ";
    for (int i = 4; i <= 6; i++)
    {
        if (board[i] == 5)
        {
            cout << "5"<< " ";
            cout <<"| ";

        }
        else if (board[i] == 3)
        {
            cout << "3" << " ";
            cout <<"| ";
        }
        else
        {
            cout << board[i] << " ";
            cout <<"| ";
        }
    }
    cout << endl;
    cout << "-------------" << endl;
    cout <<"| ";
    for (int i = 7; i <= 9; i++)
    {
        if (board[i] == 5)
        {
            cout << "5" << " ";
            cout <<"| ";
        }
        else if (board[i] == 3)
        {
            cout << "3" << " ";
            cout <<"| ";
        }
        else
        {
            cout << board[i] << " ";
            cout <<"| ";
        }
    }
    cout << endl;
    cout << "-------------" << endl;
}


int posswin(int p)
{
  int target;
  // x
  if(p == 1)
  {
    target = 18;
  }
  else
  {
    target = 50;
  }
  
  // row check
  for(int i=1; i<=7; i+=3)
  {
    if(board[i] * board[i+1] * board[i+2] == target)
    {
      if(board[i] == 2)
      {
        return i;
      }
      else if(board[i+1] == 2)
      {
        return i+1;
      }
      else
      {
        return i+2;
      }
    }
  }
  
  // col check
  for(int i=1; i<=3; i++)
  {
    if(board[i] * board[i+3] * board[i+6] == target)
    {
      if(board[i] == 2)
      {
        return i;
      }
      else if(board[i+3] == 2)
      {
        return i+3;
      }
      else
      {
        return i+6;
      }
    }
  }
  
   // left diagonal
    if (board[1] * board[5] * board[9] == target)
    {
        if (board[1] == 2)
        {
            return 1;
        }
        if (board[5] == 2)
        {
            return 5;
        }
        else
        {
            return 9;
        }
    }
    // right diagonal
    if (board[3] * board[5] * board[7] == target)
    {
        if (board[3] == 2)
        {
            return 3;
        }
        if (board[5] == 2)
        {
            return 5;
        }
        else
        {
            return 7;
        }
    }
    return 0;
}

void TicTacToe()
{
    switch(turn)
    {
      case 1:
      
        GO(turn);
        printBoard();
        break;
      case 2:
        if(board[5] == 2)
        {
          GO(5);
        }
        else
        {
          GO(1);
        }
        printBoard();
        break;
      case 3:
        if(board[9] == 2)
        {
          GO(9);
        }
        else
        {
          GO(5);
        }
        printBoard();
        break;
      case 4:
        if(posswin(1) != 0)
        {
          GO(posswin(1));
        }
        else
        {
          GO(Make2());
        }
        printBoard();
        break;
      case 5:
        if(posswin(1) != 0)
        {
          GO(posswin(1));
          cout << "X wins";
          return;
        }
        else if(posswin(0) != 0)
        {
          GO(posswin(0));
        }
        else if(board[7] == 2)
        {
          GO(7);
        }
        else
        {
          GO(3);
        }
        printBoard();
        break;
      case 6:
        if(posswin(0) != 0)
        {
          GO(posswin(0));
          cout << "O wins";
          return;
        }
        else if(posswin(1) != 0)
        {
          GO(posswin(1));
        }
        else
        {
          GO(Make2());
        }
        printBoard();
        break;
      case 7:
         if(posswin(1) != 0)
        {
          GO(posswin(1));
          cout << "X wins";
          return;
        }
        else if(posswin(0) != 0)
        {
          GO(posswin(0));
        }
        else
        {
          int i = findBlank();
          GO(i);
        }
        printBoard();
        break;
      case 8:
        if(posswin(0) != 0)
        {
          GO(posswin(0));
          cout << "O wins";
          return;
        }
        else if(posswin(1) != 0)
        {
          GO(posswin(1));
        }
        else
        {
          int i = findBlank();
          GO(i);
        }
        printBoard();
        break;
      case 9:
        if(posswin(1) != 0)
        {
          GO(posswin(1));
          cout << "X wins";
          return;
        }
        else if(posswin(0) != 0)
        {
          GO(posswin(0));
        }
        else
        {
          int i = findBlank();
          GO(i);
        }
        printBoard();
        break;
      default:
        break;
    }
}

int main()
{
  turn  = 1;
  cout << "Before : "<< endl;
  printBoard();
  
  while(turn <= 9)
  {
    TicTacToe();
  }

    return 0;
}