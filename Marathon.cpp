#include <iostream>
Susing namespace std;

#define MAX_P 6

struct node
{
    int timeSec;
    int energy;
};

struct node paceInfo[MAX_P] = {0};

int visited[MAX_P] = { 0 };

int H, D;
int finalTime;


void resetGlobal()
{
    for (int i = 0; i < MAX_P; i++)
        visited[i] = 0;
}


//Pure Recurrsion with Pruning
void calculate(int curr_time, int remain_dist, int remain_energy, int paceIndex)
{
    if (curr_time > finalTime){
        return;
    }

    if (remain_energy<0){
        return;
    }

    if (remain_dist <= 0){
        if (curr_time < finalTime){
            finalTime = curr_time;
        }
        return;
    }

    if ((remain_dist * paceInfo[5].energy) > remain_energy){
        return;
    }

    if (paceIndex == 1)
        calculate(paceInfo[1].timeSec + curr_time, remain_dist - 1, remain_energy - paceInfo[1].energy, 1);
    if (paceIndex == 2 || paceIndex == 1)
        calculate(paceInfo[2].timeSec + curr_time, remain_dist - 1, remain_energy - paceInfo[2].energy, 2);
    if (paceIndex == 3 || paceIndex == 1 || paceIndex == 2)
        calculate(paceInfo[3].timeSec + curr_time, remain_dist - 1, remain_energy - paceInfo[3].energy, 3);
    if (paceIndex == 4 || paceIndex == 1 || paceIndex == 2 || paceIndex == 3)
        calculate(paceInfo[4].timeSec + curr_time, remain_dist - 1, remain_energy - paceInfo[4].energy, 4);
    if (paceIndex == 5 || paceIndex == 1 || paceIndex == 2 || paceIndex == 3 || paceIndex == 4)
        calculate(paceInfo[5].timeSec + curr_time, remain_dist - 1, remain_energy - paceInfo[5].energy, 5);
}


//Only For loop Soluion and fastest
void comuteForLoopMin() //Working
{

    for (int m = 0; m <= H / paceInfo[4].energy && m <= D; m++)
    for (int k = 0; k <= H / paceInfo[3].energy && k <= D; k++)
    for (int j = 0; j <= H / paceInfo[2].energy && j <= D; j++)
    for (int i = 0; i <= H / paceInfo[1].energy && i <= D; i++)
    {
        int n = (D - (i + j + k + m));

        int tempTime = i*paceInfo[1].timeSec + j*paceInfo[2].timeSec + k*paceInfo[3].timeSec + m*paceInfo[4].timeSec + n*paceInfo[5].timeSec;

        int tempEnergy = i*paceInfo[1].energy + j*paceInfo[2].energy + k*paceInfo[3].energy + m*paceInfo[4].energy + n*paceInfo[5].energy;

        if (tempEnergy > H)
            continue;
        if (finalTime > tempTime)
            finalTime = tempTime;
    }
}

//Recursion with For Loop
void ComputeRecurssion(int tmpDist, int tmpEnergy, int tmpTime, int node)
{

    if (tmpTime > finalTime)
        return;

    if (tmpEnergy > H)
        return;

    if (tmpDist == D)
    {
        if (finalTime > tmpTime)
            finalTime = tmpTime;
        return;
    }


    for (int i = node; i <= 5; i++)
    {
        //if (visited[i] == 0)
        {
            visited[i] = 1;
            int j = 1; //  5;

            while (1)
            {
                if (j*paceInfo[i].energy + tmpEnergy <= H && j + tmpDist <= D)
                {
                    ComputeRecurssion(j + tmpDist, j*paceInfo[i].energy + tmpEnergy, tmpTime + j*paceInfo[i].timeSec, i+1);
                }
                else
                    break;
                j++; // =5;
            }
        }
        //backtrack
        visited[i] = 0;
    }
}

int main(int argc, char** argv)
{
    int T, test_case;
   // freopen("input.txt", "r", stdin);

    cin >> T;
    for (test_case = 0; test_case < T; test_case++)
    {
        int tempMin = 0, tempSec = 0;
        cin >> H >> D;
        finalTime = 9999999;
        resetGlobal();
        for (int i = 1; i <= 5; i++)
        {
            cin >> tempMin >> tempSec;
            paceInfo[i].timeSec = tempMin * 60 + tempSec;

            cin >> paceInfo[i].energy;
        }
        //Logic here

        //comuteForLoopMin();
        //ComputeRecurssion(0,0,0, 1);
        calculate(0, D, H, 1);

        // Print the answer to standard output(screen).
        cout << "Case #" << test_case + 1 << " " << (finalTime/60)<<" "<<(finalTime%60)<<endl;
    }

    return 0;//Your program should return 0 on normal termination.
}
