#include <stdio.h>
#include <time.h>
#define GAS 1
#define DIESEL 2
#define NOTHING 0
#define RIGHT 1
#define LEFT -1
#define SPOT 10

int A[SPOT];
int min;
struct Cars {
    int Visited[SPOT];
    int nc;//no of cars
};

void fill(int step,int direction,int fuel,int quantity,int count,int cars_left,struct Cars station)
{    if(count == min)
        return;
    if(step == 0)
    {//GASOLINE station
        fill(1,RIGHT,GAS,2,count+1,cars_left,station);
        return;
    }if(step == SPOT-1)
    {//DIESEL station
        fill(SPOT-2,LEFT,DIESEL,2,count+1,cars_left,station);
        return;
    }if(A[step]==0)
    {//spot not occupied by any car count does not increase
        fill(step+direction,direction,fuel,quantity,count, cars_left,station);
    }
    if(A[step]==fuel&&station.Visited[step]==0&&quantity>0)
    {//fill
        station.Visited[step]=1;
        if(cars_left == 1)
        {    if(count < min)
                min = count;
            return;
        }//go forward
        fill(step+direction,direction,fuel,quantity-1,count+1,cars_left-1,station);
        //go back direction
        fill(step-direction,-(direction),NOTHING,0,count+1,cars_left-1,station);
        //don't fill and go forward
        station.Visited[step]=0;
        fill(step+direction,direction,fuel,quantity,count+1,cars_left,station);
    }
    else
    {//Already filled
        fill(step+direction,direction,fuel,quantity,count+1,cars_left,station);
    }
}

int main()
{
    int T,i;
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    //freopen("input.txt", "r", stdin);
    scanf("%d",&T);
    for(i=0;i<T;i++)
    {    struct Cars station;
        int j;
        min = 65530;    //reset  all data
        for(j=0;j<SPOT;j++)
        {    A[j]=0;
            station.Visited[j]=0;
        }//read ip
        scanf("%d",&station.nc);
        for(j=1;j<=station.nc;j++)
        {
            scanf("%d",&A[j]);
        }
        fill(0,RIGHT,GAS,2,0,station.nc,station);
        fill(0,RIGHT,NOTHING,2,0,station.nc,station);
        printf("%d %d\n",i+1,min);
    }
     end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("%f",cpu_time_used );
    return 0;
}
