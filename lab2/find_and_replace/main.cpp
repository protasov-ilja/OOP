// find_and_replace.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "FindAndReplace.h"

using namespace std;

void CopyWithReplace(const string& searchedString, const string& replacedString);
bool ReplaceStringsInStream(const string& searchedString, const string& replacedString);

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: find_and_replace.exe <search string> <replace string>\n";
		return 1;
	}

	bool isSuccess = ReplaceStringsInStream(argv[1], argv[2]);
	if (!isSuccess)
	{
		return 1;
	}

	return 0;
}

bool ReplaceStringsInStream(const string& searchedString, const string& replacedString)
{
	if (searchedString.empty())
	{
		cout << "You wrote empty searching string in argument #1\n";
		return false;
	}

	CopyWithReplace(searchedString, replacedString);

	if (!cout.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}

	return true;
}

void CopyWithReplace(const string& searchedString, const string& replacedString)
{
	string text;
	while (getline(cin, text))
	{
		text = FindAndReplace(text, searchedString, replacedString);
		cout << text << '\n';
	}
}
