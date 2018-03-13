// dictonary.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WorkWithDictionary.h"
#include "windows.h"
#include <fstream>

void ReadDictionaryFromFileToMap(const std::string& dictionaryFileName, std::map<std::string, std::string>& dictionary);
void SaveChangesInDictionaryToFile(const std::string& dictionaryFileName, const std::map<std::string, std::string>& dictionary);

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n"
				  << "Usage: dictonary.exe <dictonary file>" << std::endl;
		return 1;
	}

	std::map<std::string, std::string> dictionary;
	ReadDictionaryFromFileToMap(argv[1], dictionary);

	bool isNeedToSaveChanges = InteractWithUser(dictionary);
	if (isNeedToSaveChanges)
	{
		SaveChangesInDictionaryToFile(argv[1], dictionary);
	}

	return 0;
}

void ReadDictionaryFromFileToMap(const std::string& inputFileName, std::map<std::string, std::string>& dictionaryMap)
{
	std::ifstream fileIn(inputFileName);
	if (fileIn.is_open())
	{
		std::string englishTranslation;
		std::string russianTranslation;

		while (getline(fileIn, englishTranslation))
		{
			getline(fileIn, russianTranslation);
			dictionaryMap.insert(std::pair<std::string, std::string>(englishTranslation, russianTranslation));
		}
	}
}

void SaveChangesInDictionaryToFile(const std::string& outputFileName, const std::map<std::string, std::string>& dictionaryMap)
{
	std::ofstream fileOut(outputFileName);
	if (fileOut.is_open())
	{
		for (auto x : dictionaryMap)
		{
			fileOut << x.first << "\n"
					<< x.second << "\n";
		}

		if (!fileOut.flush())
		{
			std::cout << "can't save data on disk" << std::endl;
		}
	}
}
