// findstring.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

string FindStringInLineAndReplace(string currString, const string& searchedString, const string& replacedString);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: findtext.exe <file name> <text to search>\n";
		return 1;
	}

	ifstream fileIn(argv[1]);
	if (!fileIn.is_open())
	{
		cout << "Failed to open " << argv[1] << " for reading\n";
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
			currString = FindStringInLineAndReplace(currString, searchedString, replacedString);

		cout << currString << endl;
	}

	return 0;
}

string FindStringInLineAndReplace(string currString, const string& searchedString, const string& replacedString)
{
	size_t searchPos = 0;

	while ((searchPos = currString.find(searchedString, searchPos)) != string::npos)
	{
		currString.replace(searchPos, searchedString.length(), replacedString);
		searchPos += replacedString.length();
	}
	return currString;
}
