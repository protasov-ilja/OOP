// lab0.1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

int main()
{
	int i;
	for (i = 100; i > 0; i -= 2)
	{
		printf("%d", i);
		if (i != 2)
		{
			printf(", ");
		}
	}

	printf("\n");

	return 0;
}
