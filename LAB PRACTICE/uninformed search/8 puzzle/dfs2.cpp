#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

#define N 3

struct Node
{
    Node* parent;
    int mat[N][N];
    int x, y;
    int level;
};

void printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            cout << mat[i][j] << " ";
        cout << endl;
    }

}

Node* newNode(int mat[N][N], int x, int y, int newX,int newY, int level, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;

    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->level = level;
    node->x = newX;
    node->y = newY;

    return node;
}

bool isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}

bool isEqual(int mat1[N][N], int mat2[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (mat1[i][j] != mat2[i][j])
                return false;
    return true;
}

void printPath(Node* root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
    cout<<"Depth :"<<root->level<<endl;
    cout << endl;
}

int row[] = {0, -1, 1, 0 };
int col[] = {-1, 0, 0, 1 };

bool dfs(int final[N][N],Node* root, int depth){
    if (isEqual(final,root->mat))
    {
        printPath(root);
        return true;
    }
    if(depth<=0){
        return false;
    }
    for (int i = 0; i < 4; i++)
    {
        int newx=root->x+row[i];
        int newy=root->y+col[i];
        if (isSafe(newx,newy))
        {
            Node *child=newNode(root->mat,root->x,root->y,newx,newy,root->level+1,root);
            if (dfs(final,child,depth-1))
            {
                return true;
            }   
        }  
    }
    return false;
    
}
void solve(int initial[N][N],int x,int y,int final[N][N],int depth){
    Node* root= new Node;
    root=newNode(initial,x,y,x,y,0,NULL);
    if (!dfs(final,root,depth))
    {
        cout<<"Solution Doesn't Exist upto that level "<<endl;
    }
}
int main()
{
    int initial[N][N] =
    {
        {1, 2, 3},
        {5, 6, 0},
        {7, 8, 4}
    };

    int final[N][N] =
    {
        {1, 2, 3},
        {0, 5, 6},
        {7, 8, 4}
    };

    int x = 1, y = 2;
    int depth = 10; 
    solve(initial, x, y, final, depth);

    return 0;
}