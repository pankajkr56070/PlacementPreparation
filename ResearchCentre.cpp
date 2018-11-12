/*
You should use the statndard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful.
*/

#include <stdio.h>

int Answer = 9999;
int region[22][22];
int visited[22][22];
int N, C;
int location[5][2];
int rear = -1;
int front = -1;
struct queue {
	int row;
	int col;
}Q[10000];

void init()
{
	int m,n;
	rear = -1;
	front = -1;
	for(m = 0; m < 22; m++)
	{
		for(n = 0; n < 22; n++)
		{
			visited[m][n] = 0;
		}
	}

	for(m = 0; m < 10000; m++)
	{
		Q[m].row = 0;
		Q[n].col = 0;
	}
}

void discover(int row, int col, int val)
{
	int l, m, k;
	int cnt = 0;

	for(k = 0; k < C; k++)
	{
		if(visited[location[k][0]][location[k][1]] > 0)
			cnt++;
	}
	if(cnt >= C)
		return;

	if((row-1) >= 1 && visited[row-1][col] == 0 && (region[row-1][col] == 1 || region[row-1][col] == 3))
	{
		visited[row-1][col] = val+1;
		++rear;
		Q[rear].row = row-1;
		Q[rear].col = col;
	}
	if((row+1) <= N && visited[row+1][col] == 0 && (region[row+1][col] == 1 || region[row+1][col] == 3))
	{
		visited[row+1][col] = val+1;
		++rear;
		Q[rear].row = row+1;
		Q[rear].col = col;
	}
	if((col-1) >= 1 && visited[row][col-1] == 0 && (region[row][col-1] == 1 || region[row][col-1] == 3))
	{
		visited[row][col-1] = val+1;
		++rear;
		Q[rear].row = row;
		Q[rear].col = col-1;
	}
	if((col+1) <= N && visited[row][col+1] == 0 && (region[row][col+1] == 1 || region[row][col+1] == 3))
	{
		visited[row][col+1] = val+1;
		++rear;
		Q[rear].row = row;
		Q[rear].col = col+1;
	}

	while(front<rear)
	{
		++front;
		discover(Q[front].row, Q[front].col, visited[Q[front].row][Q[front].col]);
	}


}


int main(void)
{
	int T, test_case;
	 scanf("%d", &T);
	for(test_case = 0; test_case < T; test_case++)
	{
		int i,j,k;
		int x,y,c;
		int temp = 0;

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
		   Implement your algorithm here.
		   The answer to the case will be stored in variable Answer.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////
		Answer = 9999;

		scanf("%d%d", &N, &C);

		for(i = 0; i < C; i++)
		{
			scanf("%d%d", &x, &y);
			location[i][0] = x;
			location[i][1] = y;
		}

		for(i = 1; i <= N; i++)
		{
			for(j = 1; j <= N; j++)
			{
				scanf("%d", &region[i][j]);
			}
		}
		for(k = 0; k < C; k++)
		{
			region[location[k][0]][location[k][1]] = 3;
		}

		init();
		Answer = 9999;
		for(i = 1; i <= N; i++)
		{
			for(j = 1; j <= N; j++)
			{
				init();
				temp = 0;
				if(region[i][j] == 1)
				{
					visited[i][j] = 1;
					discover(i, j, 1);
					for(k = 0; k < C; k++)
					{
						if(temp < visited[location[k][0]][location[k][1]])
							temp = visited[location[k][0]][location[k][1]];
					}
					if(Answer > temp)
						Answer = temp;
				}

			}

		}
	printf("#%d %d\n", test_case+1, Answer-1);

	}

	return 0;//Your program should return 0 on normal terminati
}
