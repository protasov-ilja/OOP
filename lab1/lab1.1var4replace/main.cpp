// lab1.1var4replace.cpp: определяет точку входа для консольного приложения.
// Find a substring in a text file and replace it with another string

#include "stdafx.h"

using namespace std;

string FindStringInLineAndReplace(const string& currString, const string& searchedString, const string& replacedString);
void CopyFileWithReplace(ifstream& fileIn, ofstream& fileOut, const string& searchedString, const string& replacedString);
bool ReplaceStringsInFile(const string& inputFileName, const string& outputFileName, const string& searchedString, const string& replacedString);

int main(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: replace.exe <input file> <output file> <search string> <replace string>\n";
		return 1;
	}

	bool isSuccess = ReplaceStringsInFile(argv[1], argv[2], argv[3], argv[4]);
	if (!isSuccess)
	{
		return 1;
	}
	return 0;
}

bool ReplaceStringsInFile(const string& inputFileName, const string& outputFileName, const string& searchedString, const string& replacedString)
{
	ifstream fileIn(inputFileName);
	if (!fileIn.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	ofstream fileOut(outputFileName);
	if (!fileOut.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing\n";
		return false;
	}

	if (searchedString == "")
	{
		cout << "You wrote empty searching string in argument #3\n";
		return false;
	}

	CopyFileWithReplace(fileIn, fileOut, searchedString, replacedString);
	if (!fileOut.flush())
	{
		cout << "Failed to save data on disk\n";
		return false;
	}

	return true;
}

void CopyFileWithReplace(ifstream& fileIn, ofstream& fileOut, const string& searchedString, const string& replacedString)
{
	string currString;
	while (getline(fileIn, currString))
	{
		currString = FindStringInLineAndReplace(currString, searchedString, replacedString);
		fileOut << currString << '\n';
	}
}

string FindStringInLineAndReplace(const string& currString, const string& searchedString, const string& replacedString)
{
	if (searchedString.length() <= currString.length())
	{
		size_t searchPos = 0;
		size_t initialСopyPosition = 0;
		string newString = "";
		while ((searchPos = currString.find(searchedString, searchPos)) != string::npos)
		{
			newString.append(currString, initialСopyPosition, searchPos - initialСopyPosition);
			newString.append(replacedString);
			searchPos += searchedString.length();
			initialСopyPosition = searchPos;
		}

		newString.append(currString, initialСopyPosition, currString.length() - initialСopyPosition);

		return newString;
	}
	return currString;
}
