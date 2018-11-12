#include<iostream>

using namespace std;

int N;
int ANS = 100000000;
int T[30];
int C[30];
//c1: soldiers with remaining life count of 1
//c2: soldiers with remaining life count of 2
//c1: soldiers with remaining life count of 3
void solve(int n,int c1,int c2,int c3,int ans){
   //Pruning
   if(ANS < ans){
      return;
   }

   //Exit Condition
   if(n == N){
       if(ANS > ans){
          // get minimum answer
          ANS = ans;
        }
        return;
   }

   int count = c1+c2+c3;
   if(T[n] <= count){
       //Fight with army
       if(T[n] <= c1){
           solve(n+1,c2,c3,0,ans);
       }else if(T[n] <= (c1+c2)){
           solve(n+1,c2-(T[n]-c1),c3,0,ans);
       }else{
           solve(n+1,0,c3-(T[n]-c1-c2),0,ans);
       }
   }

   //Pass the station
   solve(n+1,c1,c2,c3,ans+C[n]);

   // Hire the Army
   solve(n+1,c1,c2,c3+T[n],ans+2*C[n]);
}
int main(){
   int t;
   cin>>t;
   while(t--){
      ANS=100000000;
      cin>>N;
      for(int i = 0;i < N;i++){
	cin>>T[i];
	cin>>C[i];
      }
      solve(0,0,0,0,0);
      cout<<ANS<<endl;
    }
    return 0;
}
