#include "stdafx.h"
#include "WorkWithDictionary.h"

bool InteractWithUser(DictionaryMap& dictionary)
{
	bool areNewTranslationsAdded = false;
	const std::string WORD_FOR_EXIT = "...";
	std::cout << "������� ����� ����� �������� ��� ������� ��� \"" << WORD_FOR_EXIT << "\" ��� ������ �� ���������\n";
	std::string userResponse;
	while (std::getline(std::cin, userResponse) && (userResponse != WORD_FOR_EXIT))
	{
		if (!FindAndDisplayTranslation(dictionary, userResponse))
		{
			if (TryToAddNewTranslation(dictionary, userResponse))
			{
				areNewTranslationsAdded = true;
			}
		}
	}

	if (areNewTranslationsAdded)
	{
		areNewTranslationsAdded = CheckForConfirmationOfSavingDictionary();
	}

	return areNewTranslationsAdded;
}

bool FindAndDisplayTranslation(const DictionaryMap& dictionary, const std::string& searchWord)
{
	auto iterator = dictionary.find(searchWord);
	if (iterator != dictionary.end())
	{
		std::cout << iterator->second << "\n";
		return true;
	}

	return false;
}

bool TryToAddNewTranslation(DictionaryMap& dictionary, const std::string& text)
{
	std::cout << "����������� ����� \"" << text << "\" ������� ������� ��� ������ ������ ��� ������.\n";
	std::string translation;
	getline(std::cin, translation);
	bool needToAddTranslation = CheckTranslationString(text, translation);
	if (needToAddTranslation)
	{
		AddTranslationInDictionary(dictionary, text, translation);
	}

	return needToAddTranslation;
}

bool CheckTranslationString(const std::string& wordForTranslation, const std::string& translation)
{
	if (translation.empty())
	{
		std::cout << "����� " << wordForTranslation << " ���������������.\n";
		return false;
	}

	return true;
}

void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& translation)
{
	std::cout << "����� \"" << wordForTranslation << "\" ��������� � ������� ��� \"" << translation << "\".\n";
	dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, translation));
}

bool CheckForConfirmationOfSavingDictionary()
{
	std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	if ((userResponse == "y") || (userResponse == "Y"))
	{
		std::cout << "��������� ���������. �� ��������." << std::endl;
		return true;
	}

	std::cout << "��������� �� ����� ���������. �� ��������." << std::endl;

	return false;
}
