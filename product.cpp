#include <string>
#include <vector>
#include <iostream>
#include <limits>

//Complexity can be 8c3 * 10^6(choosing 3 out of 8 products * (choosing 0 to mx possible (100*100*100))
class Product_BruteForce
{
public:
	static int CPU;
	static int MEM;
	static int BRD;
	static int CPU_COST;
	static int MEM_COST;
	static int N;

public:
	class Pro
	{
	public:
		int c = 0;
		int m = 0;
		int b = 0;
		int v = 0;

		Pro(int _c, int _m, int _b, int _v);
	};

public:
	static std::vector<Pro*> products;

	static std::vector<int> MAXNUM;

	static void main(std::vector<std::wstring> &args) throw(FileNotFoundException);

private:
	static bool canProceed(std::vector<int> &remaining);

	static void increse(std::vector<int> &remaining, Pro *pro, int x);

	static bool decrese(std::vector<int> &remaining, Pro *pro, int i);

	static int findMax(Pro *p);
};


int Product_BruteForce::CPU = 0;
int Product_BruteForce::MEM = 0;
int Product_BruteForce::BRD = 0;
int Product_BruteForce::CPU_COST = 0;
int Product_BruteForce::MEM_COST = 0;
int Product_BruteForce::N = 0;

Product_BruteForce::Pro::Pro(int _c, int _m, int _b, int _v)
{
	c = _c;
	m = _m;
	b = _b;
	v = _v;
}

std::vector<Pro*> Product_BruteForce::products(8);
std::vector<int> Product_BruteForce::MAXNUM(8);

void Product_BruteForce::main(std::vector<std::wstring> &args) throw(FileNotFoundException)
{
	FileInputStream tempVar(L"product.txt");
	Scanner *sc = new Scanner(&tempVar);

	int T = sc->nextInt();
	for (int t = 1; t <= T; t++)
	{
		long long time = System::currentTimeMillis();
		CPU = sc->nextInt();
		MEM = sc->nextInt();
		BRD = sc->nextInt();
		CPU_COST = sc->nextInt();
		MEM_COST = sc->nextInt();
		N = sc->nextInt();
		for (int i = 0; i < N; i++)
		{
			products[i] = new Pro(sc->nextInt(), sc->nextInt(), sc->nextInt(), sc->nextInt());
			MAXNUM[i] = findMax(products[i]);
		}

		int MAX = std::numeric_limits<int>::min();
		// The Brute force approach

		for (int i = 0; i < N; i++)
		{ //for loop 1 for 1st product out of 3 choosen products
			for (int j = 0; j < N; j++)
			{ //for loop 2 for 1st product out of 3 choosen products
				for (int k = 0; k < N; k++)
				{ //for loop 3 for 1st product out of 3 choosen products
					std::vector<int> remaining = {CPU, MEM, BRD};
					for (int x = 0; x <= MAXNUM[i]; x++)
					{ //inner loop to cover by taking product-1 out of choosen products from 0 to MAX possible if we take only this product
						if (!decrese(remaining, products[i], x))
						{
							break;
						}
						int y = 0;
						for (; y <= MAXNUM[j]; y++)
						{ //inner loop to cover by taking product-2 out of choosen products from 0 to MAX possible if we take only this product
							if (!decrese(remaining, products[j], y))
							{
								y++;
								break;
							}
							int z = 0;
							for (; z <= MAXNUM[k]; z++)
							{ //inner loop to cover by taking product-3 out of choosen products from 0 to MAX possible if we take only this product
								if (!decrese(remaining, products[k], z))
								{
									z++;
									break;
								}

								int current = x * products[i]->v + y * products[j]->v + z * products[k]->v + remaining[0] * CPU_COST + remaining[1] * MEM_COST;
								MAX = std::max(MAX, current);
								if (k < 2)
								{ //To cover N<3 cases
									z++;
									break;
								}
							}
							increse(remaining, products[k], z - 1);
							if (j < 1)
							{ //To cover N<3 cases
								y++;
								break;
							}
						}

						increse(remaining, products[j], y - 1);
					}
				}
				if (j >= N - 1) //To cover N<3 cases
				{
					break;
				}
			}

			if (i >= N - 2) //To cover N<3 cases
			{
				break;
			}
		}
		std::wcout << L"#" << t << L" " << MAX << std::endl;
		std::wcout << L"#time = " << static_cast<double>(System::currentTimeMillis() - time) / 1000 << std::endl;
	}

}

bool Product_BruteForce::canProceed(std::vector<int> &remaining)
{
	if (remaining[0] < 0 || remaining[1] < 0 || remaining[2] < 0)
	{
		return false;
	}
	return true;
}

void Product_BruteForce::increse(std::vector<int> &remaining, Pro *pro, int x)
{
	remaining[0] += pro->c * x;
	remaining[1] += pro->m * x;
	remaining[2] += pro->b * x;
}

bool Product_BruteForce::decrese(std::vector<int> &remaining, Pro *pro, int i)
{
	if (i != 0)
	{
		remaining[0] -= pro->c;
		remaining[1] -= pro->m;
		remaining[2] -= pro->b;
	}
	return canProceed(remaining);
}

int Product_BruteForce::findMax(Pro *p)
{

	if ((p->c * CPU_COST + p->m * MEM_COST) >= p->v)
	{
		return 0;
	}
	return std::min(std::min(BRD / p->b, CPU / p->c), MEM / p->m);
}
