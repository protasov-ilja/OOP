// task1var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CVector3D.h"
#include <iostream>

int main()
{
	int y1 = 1;
	(y1 += y1) += y1;
	std::cout << y1 << std::endl;
	CVector3D x1(1, 0, 0);
	(x1 += x1) += x1;
	std::cout << x1;

    return 0;
}

