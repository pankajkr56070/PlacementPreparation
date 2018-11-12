#include<bits/stdc++.h>
using namespace std;

#define V 5

bool isSafe(bool graph[V][V],int vertex ,int color[],int c){

for(int i=0;i<V;i++){
    if(graph[vertex][i] && c == color[i])
        return false;
}
return true;
}
bool coloringUtil(bool graph[V][V],int m,int color[],int vertex){

if(vertex==V)
    return true;
for(int i=1;i <= m;i++){
    if(isSafe(graph,vertex,color,i)){
        color[vertex]=i;
        if(coloringUtil(graph,m,color,vertex+1)==true)
            return true;
        color[vertex]=0;
    }
}
return false;
}

void mColoring(bool graph[V][V],int m){
int* color=new int[V];
for(int i=0;i < V;i++)
    color[i]=0;
if(coloringUtil(graph,m,color,0)==false)
    cout<<-1<<"\n";
else{
    cout<<1<<endl;
    for(int i=0;i <V;i++)
        cout<<color[i]<<" ";
}
}

int main(){
bool graph[V][V]={0};
int edges;
cin>>edges;
for(int i=0;i < edges;i++){
    int a,b;
    cin>>a>>b;
    graph[a][b]=1;
    graph[b][a]=1;
}
mColoring(graph,2);
return 0;
}
