#include<iostream>
using namespace std;

#define Max 100000
#define ROWS 50
#define COLS 50

int mat[ROWS][COLS];
int visited[ROWS][COLS];
int depth[ROWS][COLS];

int f=0;
int r=0;

struct Node{
int x,y,d;
};

Node q[Max];
void push(int a,int b,int d){
Node temp;
temp.x=a;
temp.y=b;
temp.d=d;
q[r++]=temp;
visited[a][b]=1;
}

Node pop(){
Node temp;
temp.x=q[f].x;
temp.y=q[f].y;
temp.d=q[f].d;
f++;
return temp;
}

bool east(int x,int y){
if(x >= 0 && x < ROWS && y >= 0 && y < COLS && visited[x][y]==0 &&
    (mat[x][y]==1 || mat[x][y]==3 || mat[x][y]==6 || mat[x][y]==7))
        return true;
else
    return false;
}

bool north(int x,int y){
if(x >= 0 && x < ROWS && y >= 0 && y < COLS && visited[x][y]==0 &&
    (mat[x][y]==1 || mat[x][y]==2 || mat[x][y]==5 || mat[x][y]==6))
        return true;
else
    return false;
}

bool west(int x,int y){
if(x >= 0 && x < ROWS && y >= 0 && y < COLS && visited[x][y]==0 &&
    (mat[x][y]==1 || mat[x][y]==3 || mat[x][y]==4 || mat[x][y]==5))
        return true;
else
    return false;
}

bool south(int x,int y){
if(x >= 0 && x < ROWS && y >= 0 && y < COLS && visited[x][y]==0 &&
    (mat[x][y]==1 || mat[x][y]==2 || mat[x][y]==4 || mat[x][y]==7))
        return true;
else
    return false;
}

void bfs(int x,int y,int d){
push(x,y,d);
while(r > f){
    Node temp=pop();
    int i=temp.x;int j=temp.y;int c=temp.d;
    depth[i][j]=c;
    if(mat[i][j]==1 || mat[i][j]==3 || mat[i][j]==4 || mat[i][j]==5){
        if(east(i,j+1))
            push(i,j+1,c+1);
    }
    if(mat[i][j]==1 || mat[i][j]==2 || mat[i][j]==5 || mat[i][j]==6){
        if(south(i+1,j))
            push(i+1,j,c+1);
    }
    if(mat[i][j]==1 || mat[i][j]==3 || mat[i][j]==6 || mat[i][j]==7){
        if(west(i,j-1))
            push(i,j-1,c+1);
    }
    if(mat[i][j]==1 || mat[i][j]==2 || mat[i][j]==4 || mat[i][j]==7){
        if(north(i-1,j))
            push(i-1,j,c+1);
        }
    }
}

int main(){

int m,n,l;
cin>>m>>n>>l;
for(int i=1; i <= m;i++){
    for(int j=1;j <= n;j++){
        cin>>mat[i][j];
        depth[i][j]=Max;
        visited[i][j]=0;
    }
}
int startingPointx,startingPointy;
cin>>startingPointx>>startingPointy;
if(mat[startingPointx+1][startingPointy+1]!=0)
    bfs(startingPointx+1,startingPointy+1,1);

int nc=0;
for(int i=1; i <= m;i++){
    for(int j=1;j <= n;j++){
        if(depth[i][j] <= l){
            nc++;
            cout<<i<<" "<<j;
            cout<<endl;
        }
    }
}
cout<<nc<<endl;
return 0;
}
