#include <stdio.h>

#define MAX 105
int N;
char map[MAX][MAX];
char res[MAX][MAX];

char visited[MAX][MAX];
int count[10];

int M_x[] = { -1, 0, +1, 0 };
int M_y[] = { 0, 1, 0, -1 };

//for storing 0 locations
int Qx[10000], Qy[10000], front, rear;
void enqueue(int x, int y) { ++rear, Qx[rear] = x; Qy[rear] = y; }
void dequeue(int*x, int*y) { ++front, *x = Qx[front]; *y = Qy[front]; }
int queue_empty() { return front == rear; }

//for BFS processing of 0s
int Qzx[10000], Qzy[10000], frontz, rearz;
void enqueue_zero(int x, int y) { ++rearz, Qzx[rearz] = x; Qzy[rearz] = y; }
void dequeue_zero(int*x, int*y) { ++frontz, *x = Qzx[frontz]; *y = Qzy[frontz]; }
int zero_queue_empty() { return frontz == rearz; }

//for BFS processing of Non Zero clusters
int Qnzx[10000], Qnzy[10000], frontNZ, rearNZ;
void enqueue_non_zero(int x, int y) { ++rearNZ, Qnzx[rearNZ] = x; Qnzy[rearNZ] = y; }
void dequeue_non_zero(int*x, int*y) { ++frontNZ, *x = Qnzx[frontNZ]; *y = Qnzy[frontNZ]; }
int non_zero_queue_empty() { return frontNZ == rearNZ; }




int is_safe(int x, int y)
{
	if (x < N && x >= 0 && y >= 0 && y < N && !visited[x][y])
		return 1;

	return 0;
}
int Answer;
void reset_visited()
{
	int i, j;
	for (i = 0; i < N; i++)
	for (j = 0; j < N; j++)
		visited[i][j] = 0;

}
int find_max()
{
	int max = 0;
	int idx = -1;
	int i, j;

	for (i = 0; i < 10; i++)
	{
		if (count[i] >= max)
		{
			max = count[i];
			idx = i;
		}
	}

	return idx;

}

void BFS_Non_Zero(int x, int y, char map[][MAX])
{
	int i, j;
	int X, Y;
	int NextX, NextY;



	enqueue_non_zero(x, y);


	while (!non_zero_queue_empty())
	{
		dequeue_non_zero(&X, &Y);
		count[map[X][Y]]++;
		visited[X][Y] = 1;

		for (i = 0; i < 4; i++)
		{
			NextX = X + M_x[i];
			NextY = Y + M_y[i];
			if (is_safe(NextX, NextY))
			{
				if (map[X][Y] == map[NextX][NextY])
				{
					enqueue_non_zero(NextX, NextY);
				}
			}

		}
	}
}
void BFS_Zero(int x, int y)
{
	int i, j;
	int NextX, NextY;
	int X, Y;


	enqueue(x, y);
	enqueue_zero(x, y);

	while (!zero_queue_empty())
	{
		dequeue_zero(&X, &Y);
		visited[X][Y] = 1;

		for (i = 0; i < 4; i++)
		{
			NextX = X + M_x[i];
			NextY = Y + M_y[i];

			if (is_safe(NextX, NextY))
			{
				if (map[NextX][NextY] != 0)
				{
					BFS_Non_Zero(NextX, NextY, map);
				}
				else
				{
					enqueue_zero(NextX, NextY);
					enqueue(NextX, NextY);
				}
			}

		}
	}

}
int solve_util()
{
	int i, j, k;
	int x, y;
	int result;
	char max;
	for (i = 0; i < N; i++)
	{

		for (j = 0; j < N; j++)
		{
			reset_visited();
			front = rear = -1;
			frontz = rearz = -1;
			frontNZ = rearNZ = -1;

			if (res[i][j] == 0 && !visited[i][j])
			{
				BFS_Zero(i, j);
				max = find_max();

				while (!queue_empty())
				{
					dequeue(&x, &y);
					res[x][y] = max;
				}

				for (k = 0; k < 10; k++)
				{
					count[k] = 0;
				}

			}


		}
	}

	result = 0;
	reset_visited();
	for (i = 0; i < N; i++)
	{

		for (j = 0; j < N; j++)
		{
			if (!visited[i][j])
			{

				BFS_Non_Zero(i, j,res);
				result++;
			}
		}

	}

	return result;
}

int main(void)
{
	int T, test_case;
	int i, j;

	//freopen("input.txt", "r", stdin);


	//setbuf(stdout, NULL);

	scanf("%d", &T);
	for (test_case = 0; test_case < T; test_case++)
	{
		scanf("%d", &N);

		for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
		{
			scanf("%d", &map[i][j]);
			res[i][j] = map[i][j];
		}



		Answer = solve_util();

		// Print the answer to standard output(screen).
		printf("Case #%d\n", test_case + 1);
		printf("%d\n", Answer);
	}

	return 0;//Your program should return 0 on normal termination.
}
