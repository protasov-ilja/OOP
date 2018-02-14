// lab1.1var4replace.cpp: определяет точку входа для консольного приложения.
// Find a substring in a text file and replace it with another string

#include "stdafx.h"

using namespace std;

string findStringInLineAndReplace(string currString, const string& searchedString, const string& replacedString);

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			<< "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
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

	const string searchedString(argv[3]);
	if (searchedString == "")
	{
		cout << "You wrote empty searching string in argument #3\n";
		return 1;
	}

	const string replacedString(argv[4]);
	string currString;

	while (getline(fileIn, currString))
	{
		if (searchedString.length() <= currString.length())
		{
			currString = findStringInLineAndReplace(currString, searchedString, replacedString);
		}

		fileOut << currString << '\n';
	}

	if (!fileOut.flush())
	{
		cout << "Failed to save data on disk\n";
		return 1;
	}

	fileIn.close();
	fileOut.close();

	return 0;
}

string findStringInLineAndReplace(string currString, const string& searchedString, const string& replacedString)
{
	size_t searchPos = 0;

	while ((searchPos = currString.find(searchedString, searchPos)) != string::npos)
	{
		currString.replace(searchPos, searchedString.length(), replacedString);
		searchPos += replacedString.length();
	}

	return currString;
}