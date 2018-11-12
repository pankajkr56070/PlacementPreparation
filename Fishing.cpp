#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define MAX 3

int fishspot[61];
int gate[MAX];
int fishermen[MAX];
int N;
int visited[MAX];
int Answer;

//To unmark spots occupied by fishermen of gate# index
void reset_fishspot(int index)
{
	int i;
	for (i = 1; i <= N; i++)
		if (fishspot[i] == index + 1)
			fishspot[i] = 0;
}

// Calculate minimum distance while allotting spots to fishermen of gate# index.
// Returns number of positions possible with minimum disance.
// pos1, pos2 is used to return positions
int calculate_distance(int index, int*pos1, int *pos2, int *score)
{
	int i, sum = 0, left_min = 999999, right_min = 999999, left, right, npos = 0;
	*pos1 = *pos2 = *score = 0;

	left = right = gate[index];

	// Allot spots to all fishermen except last based on minimum distance
	for (i = 1; i < fishermen[index]; i++)
	{
		if (fishspot[gate[index]] == 0)
		{
			sum++;
			fishspot[gate[index]] = index + 1;
		}
		else
		{
			left_min = right_min = 999999;

			while ((left > 0) && (fishspot[left] > 0))
				left--;

			while ((right <= N) && (fishspot[right] > 0))
				right++;

			if ((left > 0) && (fishspot[left] == 0))
				left_min = gate[index] - left + 1;

			if ((right <= N) && (fishspot[right] == 0))
				right_min = right - gate[index] + 1;

			if (right_min == left_min)
			{
				// Place 2 fishermen, if avaiable
				if ((fishermen[index] - i - 1) > 1)
				{
					fishspot[left] = fishspot[right] = index + 1;
					sum += (2 * left_min);
					i++;

					// If all fishermen are alloted spots
					if (i == fishermen[index])
					{
						npos = 1;
						*score = sum;
						return npos;
					}
				}
				else
				{
					sum += left_min;
					fishspot[left] = index + 1;
				}
			}
			else if (left_min < right_min)
			{
				sum += left_min;
				fishspot[left] = index + 1;
			}
			else if (right_min < left_min)
			{
				sum += right_min;
				fishspot[right] = index + 1;
			}
		}
	}

	left_min = right_min = 99999;

	// Allot spot to last fishermen
	while ((left > 0) && (fishspot[left] > 0))
		left--;

	if ((left > 0) && (fishspot[left] == 0))
		left_min = gate[index] - left + 1;

	while ((right <= N) && (fishspot[right] > 0))
		right++;

	if ((right <= N) && (fishspot[right] == 0))
		right_min = right - gate[index] + 1;

	if ((sum + left_min) == (sum + right_min))
	{
		npos = 2;
		*pos1 = left;
		*pos2 = right;
		*score = sum + left_min;
	}
	else if ((sum + left_min) > (sum + right_min))
	{
		npos = 1;
		*score = sum + right_min;
		fishspot[right] = index + 1;
	}
	else if ((sum + left_min) < (sum + right_min))
	{
		npos = 1;
		*score = sum + left_min;
		fishspot[left] = index + 1;
	}

	return npos;
}

// Solve is used to select next gate and generate all combinations.
void solve(int index, int sum, int count)
{
	int npos, pos1, pos2, score, i;

	visited[index] = 1;

	if (sum > Answer)
		return;

	npos = calculate_distance(index, &pos1, &pos2, &score);
	sum += score;

	if (count == MAX)
	{
		if (Answer > sum)
			Answer = sum;

		return;
	}

	if (npos == 1)
	{
		for (i = 0; i < MAX; i++)
		{
			if (visited[i] == 0)
			{
				solve(i, sum, count + 1);
				visited[i] = 0;
				reset_fishspot(i);
			}
		}
	}
	else if (npos == 2)
	{
		fishspot[pos1] = index + 1;
		for (i = 0; i < MAX; i++)
		{
			if (visited[i] == 0)
			{
				solve(i, sum, count + 1);
				visited[i] = 0;
				reset_fishspot(i);
			}
		}

		fishspot[pos1] = 0;
		fishspot[pos2] = index + 1;
		for (i = 0; i < MAX; i++)
		{
			if (visited[i] == 0)
			{
				solve(i, sum, count + 1);
				visited[i] = 0;
				reset_fishspot(i);
			}
		}
		fishspot[pos2] = 0;
	}
}

int main()
{
	int T, testcase, i;

	scanf("%d", &T);
	for (testcase = 1; testcase <= T; testcase++)
	{
		scanf("%d", &N);
		for (i = 0; i < MAX; i++)
		{
			scanf("%d %d", &gate[i], &fishermen[i]);
			visited[i] = 0;
		}

		for (i = 1; i <= N; i++)
			fishspot[i] = 0;

		Answer = 999999;

		for (i = 0; i < MAX; i++)
		{
			solve(i, 0, 1);
			visited[i] = 0;
			reset_fishspot(i);
		}

		printf("#%d %d\n", testcase, Answer);
	}
	return 0;
}
