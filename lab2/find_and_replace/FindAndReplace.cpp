#include "stdafx.h"
#include <iostream>
#include <string>

#include "FindAndReplace.h"

using namespace std;

string FindAndReplace(const string& text, const string& stringToSearch, const string& stringToReplace)
{
	if ((stringToSearch.length() <= text.length()) && (!text.empty()) && (!stringToSearch.empty()))
	{
		size_t searchPos = 0;
		size_t initial�opyPosition = 0;
		string newString;
		while ((searchPos = text.find(stringToSearch, searchPos)) != string::npos)
		{
			newString.append(text, initial�opyPosition, searchPos - initial�opyPosition);
			newString.append(stringToReplace);
			searchPos += stringToSearch.length();
			initial�opyPosition = searchPos;
		}

		newString.append(text, initial�opyPosition, text.length() - initial�opyPosition);

		return newString;
	}

	return text;
}
