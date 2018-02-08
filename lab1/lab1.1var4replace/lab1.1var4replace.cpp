// lab1.1var4replace.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string findStringInLineAndReplaced(string currStr, string searchedStr, string replacedStr)
{
	string::size_type serachPos = currStr.find(searchedStr);
	if (string::npos == serachPos)
	{
		return currStr;
	}
	else
	{
		currStr.replace(serachPos, searchedStr.length(), replacedStr);
		return currStr;
	}
}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	if (argv[3] == "")
	{
		cout << "You wrote empty searching string in argument #3\n";
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

	string searchedString(argv[3]);
	string replacedString(argv[4]);
	string currString;

	while (getline(fileIn, currString))
	{
		if (searchedString.length() <= currString.length())
		{
			//проверяем текущую строку
			currString = findStringInLineAndReplaced(currString, searchedString, replacedString);
		}
		// выводим новую строку в файл
		fileOut << currString << '\n';
	}

	fileIn.close();
	fileOut.close();

	return 0;
}