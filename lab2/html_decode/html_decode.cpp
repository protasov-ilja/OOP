// html_decode.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

std::string HtmlDecode(std::string const& html);
void CopyWithReplace(const string& searchedString, const string& replacedString);
bool ReplaceStringsInStream(const string& searchedString, const string& replacedString);

int main()
{
	std::string text;
	while (getline(std::cin, text))
	{
		text = HtmlDecode(text);
		std::cout << text << '\n';
	}

	if (!std::cout.flush())
	{
		std::cout << "Failed to save data on disk" << std::endl;
		return false;
	}

	return 0;
}

std::string FindAndReplace(const std::string& text)
{
	const size_t MIN_LENGTH_OF_SEARCH_SUBSTR = 6;
	if ((MIN_LENGTH_OF_SEARCH_SUBSTR <= text.length()) && (!text.empty()))
	{
		vector<string>
		size_t searchPos = 0;
		size_t initialСopyPosition = 0;
		std::string newString;
		while ((searchPos = text.find("&", searchPos)) != std::string::npos)
		{
			verificationString.append(helloWorld, 0, 4);
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

std::string HtmlDecode(const std::string& html)
{

}
