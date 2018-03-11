#include "stdafx.h"
#include <iostream>
#include <string>

#include "FindAndReplace.h"

using namespace std;

string FindAndReplace(const string& text, const string& searchedString, const string& replacedString)
{
	if ((searchedString.length() <= text.length()) && (!text.empty()))
	{
		size_t searchPos = 0;
		size_t initialÑopyPosition = 0;
		string newString;
		while ((searchPos = text.find(searchedString, searchPos)) != string::npos)
		{
			newString.append(text, initialÑopyPosition, searchPos - initialÑopyPosition);
			newString.append(replacedString);
			searchPos += searchedString.length();
			initialÑopyPosition = searchPos;
		}

		newString.append(text, initialÑopyPosition, text.length() - initialÑopyPosition);

		return newString;
	}
	return text;
}
