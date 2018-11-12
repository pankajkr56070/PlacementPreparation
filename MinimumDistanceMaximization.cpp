#include<bits/stdc++.h>
using namespace std;

bool isFeasible(int arr[],int n,int mid,int k){

int pos=arr[0];
int no=1;
for(int i=1;i  < n;i++){
  if(arr[i] - pos >= mid){
    no++;
    pos=arr[i];
    if(no==k)
    return true;
  }
}
return false;
}

int binarySearch(int arr[],int n,int k){
int res=-1;
sort(arr,arr+n);
int left=arr[0];
int right=arr[n-1];
while(left  < right){
  int mid=(left+right)/2;
  if(isFeasible(arr,n,mid,k)){
    res=max(res,mid);
    left=mid+1;
  }
  else
  right=mid;
}
return res;
}

int main(){
int t;cin>>t;
while(t--){
    int n;
    cin>>n;
    int arr[n];
    for(int i=0;i < n;i++)
        cin>>arr[i];
    int k;
    cin>>k;
    cout<<binarySearch(arr,n,k)<<endl;
}

return 0;
}
