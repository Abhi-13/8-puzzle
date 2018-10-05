#include <bits/stdc++.h>
using namespace std;
#define N 3
struct Node
{
    Node* parent;
    int mat[N][N];
    int x,y;
    int cost;
    int level;
};
int printMatrix(int mat[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%d ", mat[i][j]);
        printf("\n");
    }
}
Node* newNode(int mat[N][N], int x, int y, int newX,int newY, int level, Node* parent)
{
    Node* node = new Node;
    node->parent = parent;
    memcpy(node->mat, mat, sizeof node->mat);
    swap(node->mat[x][y], node->mat[newX][newY]);
    node->cost = INT_MAX;
    node->level = level;
    node->x = newX;
    node->y = newY;
    return node;
}
int row[] = { 1, 0, -1, 0 };
int col[] = { 0, -1, 0, 1 };
int calculateCost(int initial[N][N], int final[N][N])
{
    int count = 0;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        if (initial[i][j] && initial[i][j] != final[i][j])
           count++;
    return count;
}
int manhattanCost(int initial[N][N],int final[N][N])
{
    int count=0;
    int col1[N*N],row1[N*N],col2[N*N],row2[N*N];
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            col1[initial[i][j]]=j;
            row1[initial[i][j]]=i;
            col2[final[i][j]]=j;
            row2[final[i][j]]=i;
        }
    }
    for(int i=1;i<=N*N-1;i++)
    {
        count=count + abs(col1[i]-col2[i]) + abs(row1[i]-row2[i]);
    }
    return count;
}
int euclideanCost(int initial[N][N],int final[N][N])
{
    int count=0;
    int col1[N*N],row1[N*N],col2[N*N],row2[N*N];
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            col1[initial[i][j]]=j;
            row1[initial[i][j]]=i;
            col2[final[i][j]]=j;
            row2[final[i][j]]=i;
        }
    }
    for(int i=1;i<=N*N-1;i++)
    {
        count=count + pow((col1[i]-col2[i]),2) + pow((row1[i]-row2[i]),2);
    }
    return count;
}
int isSafe(int x, int y)
{
    return (x >= 0 && x < N && y >= 0 && y < N);
}
void printPath(Node* root)
{
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);

    printf("\n");
}
struct comp
{
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};
int c2=0;
void solve(int initial[N][N], int x, int y,
           int final[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = mainatomeCost(initial, final);
    pq.push(root);
    while (!pq.empty())
    {
        c2++;
        if(c2>1e6)
        {
            cout<<"impossible";
             exit(0);
        }
        Node* min = pq.top();
        pq.pop();
        if (min->cost == 0)
        {
            printPath(min);
            return;
        }
        for (int i = 0; i < 4; i++)
        {
            if (isSafe(min->x + row[i], min->y + col[i]))
            {
                Node* child = newNode(min->mat, min->x,
                              min->y, min->x + row[i],
                              min->y + col[i],
                              min->level + 1, min);
                child->cost = manhattanCost(child->mat, final);
                pq.push(child);
            }
        }
    }
}
bool isSolvable1(int initial[N][N])
{
    vector<int> g;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            g.push_back(initial[i][j]);
        }
    }
    int count=0;
    for(int i=0;i<g.size();i++)
    {
        for(int j=i+1;j<g.size();j++)
        {
            if(g[i] && g[j] && g[i]>g[j])
            {
                count++;
            }
        }
    }
    if(count%2==0)
        return 1;
    else
        return 0;
}
bool isSolvable2(int initial[N][N],int x)
{
    vector<int> g;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            g.push_back(initial[i][j]);
        }
    }
    int count=0;
    for(int i=0;i<g.size();i++)
    {
        for(int j=i+1;j<g.size();j++)
        {
            if(g[i] && g[j] && g[i]>g[j])
            {
                count++;
            }
        }
    }
    if(count%2==1 && x%2==0)
        return 1;
    else if(count%2==0 && x%2==1)
        return 1;
    else
        return 0;
}
int main()
{
    int initial[N][N],final[N][N];
    int x,y;
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            cin>>initial[i][j];
            if(initial[i][j]==0)
            {
                x=i;
                y=j;
            }
        }
    }
    int k=1;
   for(int i=0;i<N;i++)
   {
        for(int j=0;j<N;j++)
        {
            final[i][j]=k;
            k++;
        }
   }
    final[N-1][N-1]=0;
    if(N%2==1)
    {
        bool ans=isSolvable1(initial);
        if(ans==1)
        {
            solve(initial, x, y, final);
        }
        else
        {
            cout<<"We can't reach the destination state";
        }
    }
    else
    {
         bool ans=isSolvable2(initial,N-x);
        if(ans==1)
        {
            solve(initial, x, y, final);
        }
        else
        {
            cout<<"We can't reach the destination state";
        }
    }
    return 0;
}
