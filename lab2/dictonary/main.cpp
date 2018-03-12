// dictonary.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Windows.h"
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <map>

void ReadDictionaryFromFileToMap(const std::string& dictionaryFileName, std::map<std::string, std::string>& dictionary);
void SaveChangesToFile(const std::string& dictionaryFileName, std::map<std::string, std::string>& dictionary);
bool InteractWithUser(std::map<std::string, std::string>& dictionary);
bool FindTranslation(const std::map<std::string, std::string>& dictionary, const std::string& searchWord);
bool CreateNewTranslation(std::map<std::string, std::string>& dictionary, const std::string& wordForTranslation);
bool CheckForConfirmationOfSavingDictionary();

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
	std::ifstream fileIn(argv[1]);
	if (fileIn.is_open())
	{
		ReadDictionaryFromFileToMap(argv[1], dictionary);
	}
	
	bool isNeedToSaveChanges = InteractWithUser(dictionary);
	if (isNeedToSaveChanges)
	{
		SaveChangesToFile(argv[1], dictionary);
	}

	return 0;
}

void ReadDictionaryFromFileToMap(const std::string& dictionaryFileName, std::map<std::string, std::string>& dictionary)
{
	std::ifstream fileIn(dictionaryFileName);
	if (fileIn.is_open())
	{
		std::string englishTranslation;
		std::string russianTranslation;

		while (fileIn >> englishTranslation >> russianTranslation)
		{
			dictionary.insert(std::pair<std::string, std::string>(englishTranslation, russianTranslation));
		}
	}
}

void SaveChangesToFile(const std::string& dictionaryFileName, std::map<std::string, std::string>& dictionary)
{
	std::ofstream fileOut(dictionaryFileName);
	if (fileOut.is_open())
	{
		for (auto x : dictionary)
		{
			fileOut << x.first << " " << x.second << std::endl;;
		}

		if (!fileOut.flush())
		{
			std::cout << "can't save data on disk" << std::endl;
		}
	}
}

bool InteractWithUser(std::map<std::string, std::string>& dictionary)
{
	bool isNeedSave = false;
	std::string userResponse;
	getline(std::cin, userResponse);
	while (userResponse != "...")
	{
		if (!FindTranslation(dictionary, userResponse))
		{
			if (CreateNewTranslation(dictionary, userResponse))
			{
				isNeedSave = true;
			}
		}

		getline(std::cin, userResponse);
	}

	if (isNeedSave)
	{
		return CheckForConfirmationOfSavingDictionary();
	}

	return isNeedSave;
}

bool FindTranslation(const std::map<std::string, std::string>& dictionary, const std::string& searchWord)
{
	bool isWordFound = false;
	if (dictionary.find(searchWord) != dictionary.end())
	{
		std::pair<std::string, std::string> foundPair = *dictionary.find(searchWord);
		std::cout << foundPair.second << "\n";
		isWordFound = true;
	}

	return isWordFound;
}

bool CreateNewTranslation(std::map<std::string, std::string>& dictionary, const std::string& wordForTranslation)
{
	bool isChangesMade = false;
	std::cout << "Неизвестное слово \"" << wordForTranslation << "\" Введите перевод или пустую строку для отказа.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	if (!userResponse.empty())
	{
		isChangesMade = true;
		dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, userResponse));
		std::cout << "Слово \"" << wordForTranslation << "\" сохранено в словаре как \"" << userResponse << "\".\n";
	}
	else
	{
		std::cout << "Слово " << wordForTranslation << " проигнорировано.\n";
	}

	return isChangesMade;
}

bool CheckForConfirmationOfSavingDictionary()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.";
	std::string userResponse;
	getline(std::cin, userResponse);
	std::transform(userResponse.begin(), userResponse.end(), userResponse.begin(), ::tolower);
	if (userResponse == "y")
	{
		std::cout << userResponse << std::endl;
		std::cout << "Изменения сохранены. До свидания.\n";
		return true;
	}

	return false;
}