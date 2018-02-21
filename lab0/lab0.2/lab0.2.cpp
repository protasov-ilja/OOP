// lab0.2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <assert.h>

// calculates sum of the digits of i
int SumDigits(int i)
{
	int sum = 0;

	while (i != 0)
	{
		sum += i % 10;
		i /= 10;
	}

	return sum;
}

int main(int argc, char* argv[])
{
	for (int i = 0; i <= 9; ++i)
	{
		for (int j = 0; j <= 9; ++j)
		{
			for (int k = 0; k <= 9; ++k)
			{
				int x = i * 100 + j * 10 + k;
				int sum = SumDigits(x);
				assert((i + j + k) == sum);

				if ((sum != 0) && (x % sum == 0))
				{
					printf("%d", x);

					if (x != 999)
					{
						printf(", ");
					}
					else
					{
						printf("\n");
					}
				}
			}
		}
	}

	return 0;
}
