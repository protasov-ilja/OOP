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
		size_t initial�opyPosition = 0;
		string newString;
		while ((searchPos = text.find(searchedString, searchPos)) != string::npos)
		{
			newString.append(text, initial�opyPosition, searchPos - initial�opyPosition);
			newString.append(replacedString);
			searchPos += searchedString.length();
			initial�opyPosition = searchPos;
		}

		newString.append(text, initial�opyPosition, text.length() - initial�opyPosition);

		return newString;
	}
	return text;
}
