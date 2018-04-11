// lab0.3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "stdlib.h"

int StringToInt(const char* str, bool& err);

int main(int argc, char* argv[])
{
	if (argc <= 1)
	{
		printf("Program calculates sum of its command line arguments.\nplease enter <arg1> <arg2>");
		return 0;
	}

	int sum = 0;
	int i = 1;
	bool err;
	int maxInt = StringToInt(argv[i], err);

	if (err)
	{
		printf("Argument #%d is not a number\n.", i);
		return 1;
	}
	else if (maxInt <= 0)
	{
		printf("Argument %d <= 0 \n.", maxInt);
		return 1;
	}

	int prevNum = 1;
	int currNum = 1;
	int nextNum;
	int lineLen = 2;

	printf("%d, ", currNum);

	while (maxInt - prevNum >= currNum)
	{
		nextNum = prevNum + currNum;
		if ((lineLen % 5 != 0) && (maxInt - nextNum >= currNum))
		{
			printf("%d, ", nextNum);
		}
		else
		{
			printf("%d \n", nextNum);
		}

		prevNum = currNum;
		currNum = nextNum;
		lineLen++;
	}

	return 0;
}

int StringToInt(const char* str, bool& err)
{
	char* pLastChar = NULL;
	int param = strtol(str, &pLastChar, 10);
	err = ((*str == '\0') || (*pLastChar != '\0'));
	return param;
}
