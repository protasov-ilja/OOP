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
		size_t initialÑopyPosition = 0;
		string newString;
		while ((searchPos = text.find(stringToSearch, searchPos)) != string::npos)
		{
			newString.append(text, initialÑopyPosition, searchPos - initialÑopyPosition);
			newString.append(stringToReplace);
			searchPos += stringToSearch.length();
			initialÑopyPosition = searchPos;
		}

		newString.append(text, initialÑopyPosition, text.length() - initialÑopyPosition);

		return newString;
	}

	return text;
}
