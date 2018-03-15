// dictonary.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WorkWithDictionary.h"
#include "windows.h"
#include <fstream>

void ReadDictionaryFromFileToMap(const std::string& dictionaryFileName, DictionaryMap& dictionary);
bool SaveChangesFromDictionaryToFile(const std::string& dictionaryFileName, const DictionaryMap& dictionary);

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

	DictionaryMap dictionary;
	ReadDictionaryFromFileToMap(argv[1], dictionary);

	bool isNeedToSaveChanges = InteractWithUser(dictionary);
	if (isNeedToSaveChanges)
	{
		if (!SaveChangesFromDictionaryToFile(argv[1], dictionary))
		{
			return 1;
		}
	}

	return 0;
}

void ReadDictionaryFromFileToMap(const std::string& inputFileName, DictionaryMap& dictionaryMap)
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

bool SaveChangesFromDictionaryToFile(const std::string& outputFileName, const DictionaryMap& dictionaryMap)
{
	bool isFailedToWriteToFile = false;
	std::ofstream fileOut(outputFileName);
	if (fileOut.is_open())
	{
		isFailedToWriteToFile = true;
		for (auto x : dictionaryMap)
		{
			fileOut << x.first << "\n"
					<< x.second << "\n";
		}

		if (!fileOut.flush())
		{
			std::cout << "Failed to save data on disk" << std::endl;
			isFailedToWriteToFile = false;
		}
	}

	return isFailedToWriteToFile;
}
