#include<bits/stdc++.h>
using namespace std;

int dp[4001][1001];
int cost[5]={4,5,2,3,6};
int ti[5]={200,210,230,235,215};

int main(){

for(int i=0;i <= 4000;i++){
  for(int j=0;j <= 1000;j++)
    dp[i][j]=INT_MAX;
}

for(int i=0;i <= 4000;i++)
  dp[i][0]=0;
for(int j=1;j <= 1000;j++){
  for(int i=1;i <= 4000;i++){
    for(int k=0;k < 5;k++){
      if(i-cost[k] >= 0){
        if(dp[i-cost[k]][j-1]!=INT_MAX)
        dp[i][j]=min(dp[i][j],dp[i-cost[k]][j-1]+ti[k]);
      }
    }
  }
}

int t;
cin>>t;
while(t--){
  int h,d;
  cin>>h>>d;
  cout<<dp[h][d]<<endl;
}

return 0;
}
