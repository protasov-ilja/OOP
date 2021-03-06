// task2MyArray.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MyArray.h"
#include <iostream>

struct ArrayItem
{
	ArrayItem(int value = 0)
		: value(value)
	{
	}
	int value = 0;
};

int main()
{
	CMyArray<ArrayItem> arr;
	arr.Append(1);
	arr.Append(2);
	arr.Append(3);
	arr.Append(4);
	arr.Resize(10);
	try
	{
		arr.Resize(2);
		arr.Resize(4);
		std::cout << arr.GetSize();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
