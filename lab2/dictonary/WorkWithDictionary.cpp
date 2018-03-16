#include "stdafx.h"
#include "WorkWithDictionary.h"

bool InteractWithUser(DictionaryMap& dictionary)
{
	bool isRequirePreservation = false;
	const std::string WORD_FOR_EXIT = "...";
	std::cout << "������� ����� ����� �������� ��� ������� ��� \"" << WORD_FOR_EXIT << "\" ��� ������ �� ���������\n";
	std::string userResponse;
	while (std::getline(std::cin, userResponse) && (userResponse != WORD_FOR_EXIT))
	{
		if (!FindAndDisplayTranslation(dictionary, userResponse))
		{
			if (TryToAddNewTranslation(dictionary, userResponse))
			{
				isRequirePreservation = true;
			}
		}
	}

	if (isRequirePreservation)
	{
		isRequirePreservation = CheckForConfirmationOfSavingDictionary();
	}

	return isRequirePreservation;
}

bool FindAndDisplayTranslation(DictionaryMap& dictionary, const std::string& searchWord)
{
	bool isWordFound = false;
	DictionaryMap::iterator iteratorForSearching = dictionary.find(searchWord);
	if (iteratorForSearching != dictionary.end())
	{
		std::pair<std::string, std::string> pairToDisplay = *iteratorForSearching;
		std::cout << pairToDisplay.second << "\n";
		isWordFound = true;
	}

	return isWordFound;
}

bool TryToAddNewTranslation(DictionaryMap& dictionary, const std::string& text)
{
	std::cout << "����������� ����� \"" << text << "\" ������� ������� ��� ������ ������ ��� ������.\n";
	std::string translation;
	bool isTranslationAdded;
	getline(std::cin, translation);
	if (isTranslationAdded = RequestTranslation(text, translation))
	{
		AddTranslationInDictionary(dictionary, text, translation);
	}

	return isTranslationAdded;
}

bool RequestTranslation(const std::string& wordForTranslation, const std::string& translation)
{
	if (!translation.empty())
	{
		std::cout << "����� \"" << wordForTranslation << "\" ��������� � ������� ��� \"" << translation << "\".\n";
		return true;
	}
	else
	{
		std::cout << "����� " << wordForTranslation << " ���������������.\n";
		return false;
	}
}

void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& translation)
{
	dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, translation));
}

bool CheckForConfirmationOfSavingDictionary()
{
	std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	std::transform(userResponse.begin(), userResponse.end(), userResponse.begin(), ::tolower);
	if (userResponse == "y")
	{
		std::cout << "��������� ���������. �� ��������." << std::endl;
		return true;
	}

	std::cout << "��������� �� ����� ���������. �� ��������." << std::endl;

	return false;
}
