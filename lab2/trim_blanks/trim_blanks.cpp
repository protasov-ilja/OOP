// trim_blanks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;

string TrimBlanks(const string& str);

int main()
{
	string inputString;
	while (cin)
	{
		getline(cin, inputString);
		if (inputString.empty())
		{
			cout << "You wrote empty string";
			return 1;
		}

		string outputString = TrimBlanks(inputString);
		cout << outputString << endl;
	};

	return 0;
}

string TrimBlanks(const string& str)
{
	size_t strIndex = 0;
	string newString = "";
	while ((str[strIndex] == ' ') && (strIndex < str.length()))
	{
		++strIndex;
	}

	for (size_t j = strIndex; j < str.length(); ++j)
	{
		if ((str[j] != ' ') || ((j + 1 < str.length()) && (str[j] == ' ') && (str[j + 1] != ' ')))
		{
			newString += str[j];
		}
	}

	return newString;
}
