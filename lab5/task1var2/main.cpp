// task1var2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CVector3D.h"
#include <iostream>

int main()
{
	int y = 1;
	(y += y) += y;
	std::cout << y << std::endl;
	CVector3D x(1, 0, 0);
	(x += x) += x;
	std::cout << x;
    return 0;
}

