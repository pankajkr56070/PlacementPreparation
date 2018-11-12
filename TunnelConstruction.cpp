#include <stdio.h>
int S[16][501];
int N,H,V;
int ans[16];
int final_min_cost= 60000000;// VERY_LARGE(taken around 60000000)
int new_cost;
int main()
{
	int i,j,k1,k2,v,T,test_case;
	int C1,C2,R1,R2,M1,M2;
	int max=60000000;// VERY_LARGE(60000000)
	int cost=0;
	int n1,n2,n3,n4,n5;
	scanf("%d",&T);
	for(test_case=1;test_case<=T;test_case++)
	{
		for(i=0;i<16;i++)
		{
			for(j=0;j<501;j++)
				S[i][j]=0;
		}
		for(i=0;i<16;i++)
			ans[i]=0;
		final_min_cost= 60000000;
		scanf("%d%d%d",&N,&H,&V);
		for(i=1;i<=V;i++)
		{
			for(j=1;j<=H;j++)
				scanf("%d",&S[i][j]);
		}
		scanf("%d%d%d",&C1,&R1,&M1);
		scanf("%d%d%d",&C2,&R2,&M2);

		// all inputs scanned..
		//Logic starts here
		for(v=1;v<=V;v++)  // for all the possible tunnels, find the min cost
		{
			max= 60000000;
			for(k1=0;k1<=H;k1++) // k1=0 means machine 1 works for 0 days
			{
				k2=H-k1; // k2 indicates the number of days machine 2 will work
				for(i=0;i<=k1;i++)
					cost = cost + (S[v][i]*C1);
				for(j=H;j>k1;j--)
					cost = cost + (S[v][j]*C2);
				// we have to add the cost for consecutive work.. that will be based on the number of days machine 1 and 2 have to work.. ie. k1 and k2
				if(k1>k2)// machine 1 has to work for more days than machine 2
					cost= cost + ((k1-k2-1)*R1);
				else if (k2>k1)// machine 2 has to work for more days than machine 1
					cost= cost + ((k2-k1-1)*R2);
				// this can be inferred from the example they have shown.. no need to take the combinations... since min cost will come if machines work alternate
				if(max>=cost)
					max=cost;
				cost=0; // for next iteration.
			}
			ans[v]=max; // for every possible tunnel, find the min cost
		}
		// we have to find the combination for N number of tunnels out of V possible tunnels such that cost is min
		if(N==1)
		{
			for(n1=1;n1<=V;n1++)
			{
				if(final_min_cost>=ans[n1])
					final_min_cost=ans[n1];
			}
		}
		else if(N==2)// 2 tunnels
		{
			for(n1=1;n1<=(V-((N-1)*2));n1++)
			{
				for(n2=n1+2;n2<=V;n2++)
				{
					new_cost= ans[n1]+ans[n2]+ (M1*M1 + M2*M2)*(n2-n1);
					if(final_min_cost>=new_cost)
						final_min_cost= new_cost;
				}
			}

		}
		else if(N==3)
		{
			for(n1=1;n1<=(V-((N-1)*2));n1++)
			{
				for(n2=n1+2;n2<=(V-((N-2)*2));n2++) // notice that n2<= V-((N-2)*2)... for n1 it is (N-1)
				{
					for(n3=n2+2;n3<=V;n3++)
					{
						new_cost= ans[n1]+ans[n2]+ ans[n3] + (M1*M1 + M2*M2)*(n3-n1); // last ie. n3 minus first ie. n1 (n3-n1)
						if(final_min_cost>=new_cost)
						final_min_cost= new_cost;
					}
				}
			}
		}
	//	similarly... go for (N==4) and (N==5) // using nested loops :)
		else if(N==4)
		{
			for(n1=1;n1<=(V-((N-1)*2));n1++)
			{
				for(n2=n1+2;n2<=(V-((N-2)*2));n2++)
				{
					for(n3=n2+2;n3<=(V-((N-3)*2));n3++)
					{
						for(n4=n3+2;n4<=V;n4++)
						{
							new_cost= ans[n1]+ans[n2]+ ans[n3] + ans[n4] + (M1*M1 + M2*M2)*(n4-n1); // last ie. n4 minus first ie. n1 (n4-n1)
						if(final_min_cost>=new_cost)
						final_min_cost= new_cost;
						}
					}
				}
			}
		}
		else if (N==5)
		{
			//similar code
		}
		//in place of nested loops, you can find some other way to cover all the cases

			printf("#%d %d\n",test_case,final_min_cost);
	}
	return 0;
}
