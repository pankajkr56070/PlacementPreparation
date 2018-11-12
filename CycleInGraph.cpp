#include<stdio.h>

/* Below variables were already given in the initial code*/
int N = 0, M = 0, AnswerN = 0;
int A[1000] = { 0, }, B[1000] = { 0, };
int Answer[101] = { 0, };

/* Below variables were newly added*/
int visited[101] = { 0, };
int graph[101][101] = { 0, };
int arr[101] = { 0, };
int cycle = 0;

void DFS_Visit(int v)
{
	int i = 0;

	visited[v] = 1;
	for (i = 1; i <= N; i++)
	{
		if (cycle == 0)
		{
			if (graph[v][i] == 1)
			{
				if (visited[i] == 0)
				{
					DFS_Visit(i);
				}
				else if (visited[i] == 1)
				{
					cycle = i; //To store the value of the node at which the cycle exists
					break;
				}
			}
		}
	}

    if(cycle>0)
	Answer[AnswerN++] = v; //All nodes traversed till the cycle was found will be stored. This will be modified later to save only the nodes in the cycle
	visited[v] = 2;
}

void DFS_Search()
{
	int i = 0;

	cycle = 0;
	for (i = 1; i <= N; i++)
	{
		if (cycle > 0)
			return; //If we have already found a cycle, need not search anymore.

		if (visited[i] == 0)
		{
			DFS_Visit(i);
		}
	}
}

int main()
{
	int i = 0, j = 0;
	int tc = 0, test_case = 0;

	scanf("%d", &tc); //tc - Number of test cases

	for (test_case = 1; test_case <= tc; test_case++)
	{
		/*clear the values in all arrays before starting a test case */
		for (i = 0; i <= 100; i++)
		{
			visited[i] = 0;
			Answer[i] = 0;
			arr[i] = 0;
			for (j = 0; j <= 100; j++)
			{
				graph[i][j] = 0;
			}
		}

		/* N = number of nodes. Constraint is 5<=N<=100
		   M = number of edges. Constraint is M<=1000
		*/
		scanf("%d %d", &N, &M);

		for (i = 0; i < M; i++)
		{
			scanf("%d %d", &A[i], &B[i]); //This was already given in the initial code. Otherwise this can be directly entered into the array graph[][] to simplify things.
			//To create adjacency matrix from this information
			graph[A[i]][B[i]] = 1;
		}
		DFS_Search();
//Start printing the answer
		printf("#%d ", test_case);
		if (cycle == 0)
		{
			printf(" 0\n"); // final answer- 0 when there is no cycle in the graph
		}
		else
		{ //To sort the nodes in cycle, in ascending order
			for (i = 0; i < AnswerN; i++)
			{
				arr[Answer[i]] = 1; // The node itself is used as array index.
				if (Answer[i] == cycle)
				{
					AnswerN = i + 1; //In DFS Visit along with the nodes in the cycle, the nodes traversed before cycle will also be included in Answer[]. This step is to eliminate these nodes from final answer
				}
			}
			for (i = 1; i <= N; i++)
			{
				if (arr[i] == 1)
				{
					printf(" %d", i); // final answer- nodes in ascending order when there is a cycle
				}
			}
			printf("\n");
		}
	}
	return 0;
}
