// dfs
#include <bits/stdc++.h>
using namespace std;

bool checkEqual(vector<vector<int>> &curr, vector<vector<int>> &final)
{
   return curr == final;
}

void findBlank(vector<vector<int>> curr, int &row, int &col)
{
   for (int i = 0; i < 3; i++)
   {
      for (int j = 0; j < 3; j++)
      {
         if (curr[i][j] == 0)
         {
            row = i;
            col = j;
            return;
         }
      }
   }
}

void printAns(vector<vector<vector<int>>> vec)
{
   for (auto mat : vec)
   {
      for (auto row : mat)
      {
         for (auto el : row)
         {
            cout << el << " ";
         }
         cout << endl;
      }
      cout << endl;
   }
}

bool dfs(vector<vector<int>> &curr, vector<vector<int>> &final, int depth, int row, int col, set<vector<vector<int>>> &vis, vector<vector<vector<int>>> &vec)
{
   if (depth > 10)
      return false;

   vec.push_back(curr);
   vis.insert(curr);

   if (checkEqual(curr, final))
   {
      cout << "Possible solution:" << endl
           << endl;
      printAns(vec);
      return true;
   }

   int delrow[] = {0, 0, -1, 1};
   int delcol[] = {1, -1, 0, 0};

   for (int i = 0; i < 4; i++)
   {
      int nrow = row + delrow[i];
      int ncol = col + delcol[i];

      if (nrow >= 0 && nrow < 3 && ncol >= 0 && ncol < 3)
      {
         swap(curr[row][col], curr[nrow][ncol]);
         if (!vis.count(curr))
         {
            if (dfs(curr, final, depth + 1, nrow, ncol, vis, vec))
               return true;
         }
         swap(curr[row][col], curr[nrow][ncol]);
      }
   }
   vec.pop_back();

   return false;
}

int main()
{
   vector<vector<int>> start = {{2, 8, 3},
                                {1, 6, 4},
                                {7, 0, 5}};
   vector<vector<int>> final = {{1, 2, 3},
                                {8, 0, 4},
                                {7, 6, 5}};

   int row, col;
   findBlank(start, row, col);
   vector<vector<vector<int>>> ans;
   set<vector<vector<int>>> vis;
   if (!dfs(start, final, 0, row, col, vis, ans))
      cout << "No possible solution." << endl;

   return 0;
}