#include <iostream>
#include <cstdio>
using namespace std;

#define MAX 15

int ans;
int W, H;

int arr[MAX][MAX];
int visit[MAX][MAX];

int mOdd[6][2] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 }, { -1, -1 }, { -1, 1 } };
int mEvn[6][2] = { { 0, -1 }, { 0, 1 }, { 1, 0 }, { -1, 0 }, { 1, -1 }, { 1, 1 } };

int oddY[3][2] = { { -1, -1 }, { -1, 1 }, { 1, 0 } };
int evenY[3][2] = { { 0, -1 }, { 0, 1 }, { 1, 0 } };

int oddInvY[3][2] = { { 0, -1 }, { 0, 1 }, { -1, 0 } };
int evenInvY[3][2] = { { -1, 0 }, { -1, -1 }, { -1, 1 } };

void runDFS(int i, int j, int value, int count) {
	if (count >= 4) {
		if (ans < value)
			ans = value;
		return;
	}

	for (int m = 0; m < 6; m++) {
		int x = -1, y = -1;
		if (j % 2) {
			x = i + mEvn[m][0];
			y = j + mEvn[m][1];
		}
		else {
			x = i + mOdd[m][0];
			y = j + mOdd[m][1];
		}
		if (!visit[x][y] && x >= 0 && x < H && y >= 0 && y < W) {
			visit[x][y] = 1;
			runDFS(x, y, value + arr[x][y], count + 1);
			visit[x][y] = 0;
		}
	}
}

void calculateY(int i, int j)
{
	int value = arr[i][j];
	int x = -1, y = -1;

	for (int m = 0; m < 3; m++)
	{
		if (j % 2) {
			x = i + evenY[m][0];
			y = j + evenY[m][1];
		}
		else {
			x = i + oddY[m][0];
			y = j + oddY[m][1];
		}
		if (x >= 0 && x < H && y >= 0 && y < W) {
			value += arr[x][y];
		}
		else
			return;
	}
	if (ans < value)
		ans = value;
}

void calculateInvertedY(int i, int j)
{
	int value = arr[i][j];
	int x = -1, y = -1;

	for (int m = 0; m < 3; m++)
	{
		if (j % 2) {
			x = i + evenInvY[m][0];
			y = j + evenInvY[m][1];
		}
		else {
			x = i + oddInvY[m][0];
			y = j + oddInvY[m][1];
		}
		if (x >= 0 && x < H && y >= 0 && y < W) {
			value += arr[x][y];
		}
		else
			return;
	}
	if (ans < value)
		ans = value;
}

int main() {
	int test = 0;

//	freopen("basestationhexagoninput.txt", "r", stdin);
	cin >> test;
	for (int tc = 1; tc <= test; tc++) {
		for (int i = 0; i < MAX; i++) {
			for (int j = 0; j < MAX; j++) {
				arr[i][j] = 0;
				visit[i][j] = 0;
			}
		}
		W = H = ans = 0;
		cin >> W >> H;

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				cin >> arr[i][j];
			}
		}

		for (int i = 0; i < H; i++) {
			for (int j = 0; j < W; j++) {
				visit[i][j] = 1;
				runDFS(i, j, arr[i][j], 1);
				visit[i][j] = 0;

				calculateY(i, j);

				calculateInvertedY(i, j);
			}
		}

		cout << "#" << tc << " " << ans * ans << endl;
	}

	return 0;
}
