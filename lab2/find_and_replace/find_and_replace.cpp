// find_and_replace.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

using namespace std;

string FindAndReplace(const string& currString, const string& searchedString, const string& replacedString);
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

string FindAndReplace(const string& text, const string& searchedString, const string& replacedString)
{
	if ((searchedString.length() <= text.length()) && (!text.empty()))
	{
		size_t searchPos = 0;
		size_t initialСopyPosition = 0;
		string newString;
		while ((searchPos = text.find(searchedString, searchPos)) != string::npos)
		{
			newString.append(text, initialСopyPosition, searchPos - initialСopyPosition);
			newString.append(replacedString);
			searchPos += searchedString.length();
			initialСopyPosition = searchPos;
		}

		newString.append(text, initialСopyPosition, text.length() - initialСopyPosition);

		return newString;
	}
	return text;
}
