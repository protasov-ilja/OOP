// dictonary.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "WorkWithDictionary.h"
#include "windows.h"
#include <fstream>

void ReadFromFile(const std::string& dictionaryFileName, DictionaryMap& dictionary);
bool SaveDictionaryToFile(const std::string& dictionaryFileName, const DictionaryMap& dictionary);

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
	ReadFromFile(argv[1], dictionary);

	bool needSavingChanges = InteractWithUser(dictionary);
	if (needSavingChanges)
	{
		if (!SaveDictionaryToFile(argv[1], dictionary))
		{
			return 1;
		}
	}

	return 0;
}

void ReadFromFile(const std::string& inputFileName, DictionaryMap& dictionaryMap)
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

bool SaveDictionaryToFile(const std::string& outputFileName, const DictionaryMap& dictionaryMap)
{
	std::ofstream fileOut(outputFileName);
	if (!fileOut.is_open())
	{
		std::cout << "Cant open file " << outputFileName << " for writing" << std::endl;
		return false;
	}

	for (const auto& pairToSave : dictionaryMap) // слово с пререводом
	{
		fileOut << pairToSave.first << "\n"
				<< pairToSave.second << "\n";
	}

	if (!fileOut.flush())
	{
		std::cout << "Failed to save data on disk" << std::endl;
		return false;
	}

	std::cout << "Изменения сохранены. До свидания." << std::endl;

	return true;
}
