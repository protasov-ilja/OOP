// flipbyte.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: flipbyte.exe <input file> <output file> <input byte>\n";
		return 1;
	}

	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
		return 1;

	}

	ofstream fileOut(argv[2]);
	if (!fileOut.is_open())
	{
		cout << "Failed to open " << argv[2] << " for writing\n";
		return 1;
	}

	

	// Считываем число и проверяем число ли это и принадлежит ли оно промежутку от 0 - 255
	// переводим его в байтовый формат
	// меняем местами 1 и последний биты в числе

    return 0;
}

