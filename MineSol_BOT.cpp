#include <iostream>
#include <string>
#include <math.h>

using namespace std;

struct grenade
{
	bool check = false;
	bool found = false;
};

void Grenade(int** input, int n, grenade** output);
int CheckAgain(grenade** output, int** input, int n);

void Grenade(int** input, int n, grenade** output)
{
	if (CheckAgain(output, input, n) == 2)
	{
		cout << endl;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (output[i][j].found == true) cout << char(254) << " ";
				else cout << ". ";
			}
			cout << endl;
		}
		cout << endl;
	}
	else if (CheckAgain(output, input, n) < 3)
	{
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (output[i][j].found == false && output[i][j].check == false)
				{
					output[i][j].found = true;
					Grenade(input, n, output);
					if (i == n - 1 && j == n - 1)
					{
						output[i][j].found = false;
						output[i][j].check = false;
						int temp = 0;
						for (int a = i; a >= 0; --a)
						{
							for (int b = j; b >= 0; --b)
							{
								if (temp == 1) break;
								if (b == j && a == i) continue;
								else if (output[a][b].found == true) { temp = 1;  break; }
								else output[a][b].check = false;
							}
						}
					}
					else
					{
						output[i][j].found = false;
						output[i][j].check = true;
					}
				}
			}
		}
	}
	else return;
}
int CheckAgain(grenade** output, int** input, int n)
{
	int a = 0; int b = 0;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int count = 0;
			for (int k = i - 1; k <= i + 1; ++k)
			{
				if (k >= n) break;
				else if (k < 0) continue;
				for (int l = j - 1; l <= j + 1; ++l)
				{
					if (l < 0) continue;
					else if (l >= n) break;
					else if (output[k][l].found == true) ++count;
				}
			}
			if (count > input[i][j]) ++a;
			else if (count == input[i][j])  ++b;
		}
	}
	if (a > 0) return 3;
	else if (b == n * n) return 2;
	else return 1;
}
int main()
{
	int** input, n; grenade** output; cin >> n;
	input = new int* [n]; output = new grenade * [n];
	for (int i = 0; i < n; ++i)
	{
		input[i] = new int[n]; output[i] = new grenade[n];
		for (int j = 0; j < n; ++j) cin >> input[i][j];
	}
	Grenade(input, n, output);
	system("pause");
	return 0;
}