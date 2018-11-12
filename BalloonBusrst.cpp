#include<bits/stdc++.h>
using namespace std;

int main(){
int t;
cin>>t;
while(t--){
int n;
cin>>n;
int arr[n+2];arr[0]=arr[n+1]=1;
for(int i=1;i <= n;i++)
  cin>>arr[i];
int dp[n+2][n+2];
for(int i=0;i < n+2;i++){
  for(int j=0;j < n+2;j++)
    dp[i][j]=0;
  }
for(int i=1;i <= n;i++)
    dp[i][i]=arr[i-1]*arr[i+1];
for(int len=2;len <= n;len++){
  for(int i=1;i <= n-len+2;i++){
    int j=i+len-1;
    for(int k=i;k <= j;k++)
      dp[i][j]=max(dp[i][j],dp[i][k-1]+dp[k+1][j]+arr[i-1]*arr[j+1]);
  }
}
for(int i=0;i < n+2;i++){
  for(int j=0;j < n+2;j++)
    cout<<dp[i][j]<<" ";
cout<<endl;
  }
cout<<dp[1][n]<<endl;
}
  return 0;
}
