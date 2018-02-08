// lab1.1var4replace.cpp: определяет точку входа для консольного приложения.
// Find a substring in a text file and replace it with another string

#include "stdafx.h"

using namespace std;

string findStringInLineAndReplaced(string currString, string searchedString, string replacedString)
{
	size_t serachPos = 0;

	while ((serachPos = currString.find(searchedString, serachPos)) != string::npos) {
		currString.replace(serachPos, searchedString.length(), replacedString);
		serachPos += replacedString.length();
	}

	return currString;
}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	} 
	else if (argv[3] == "\0")
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
			currString = findStringInLineAndReplaced(currString, searchedString, replacedString);
		}

		fileOut << currString << '\n';
	}

	fileIn.close();
	fileOut.close();

	return 0;
}