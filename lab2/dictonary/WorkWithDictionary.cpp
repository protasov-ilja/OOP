#include "stdafx.h"
#include "WorkWithDictionary.h"

bool InteractWithUser(DictionaryMap& dictionary)
{
	const std::string WORD_FOR_EXIT = "...";
	bool areNewTranslationsAdded = false;
	std::cout << "������� ����� ����� �������� ��� ������� ��� \"" << WORD_FOR_EXIT << "\" ��� ������ �� ���������\n";
	std::string userResponse;
	while (std::getline(std::cin, userResponse) && (userResponse != WORD_FOR_EXIT))
	{
		if (!FindAndDisplayTranslation(dictionary, userResponse))
		{
			std::string translation;
			if (ConfirmTranslationAdding(userResponse, translation))
			{
				AddTranslationInDictionary(dictionary, userResponse, translation);
				areNewTranslationsAdded = true;
			}
		}
	}

	return areNewTranslationsAdded ? ConfirmSaving() : false;
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

bool ConfirmTranslationAdding(const std::string& text, std::string& translation) // ������ ��� �������������� ����������� ������
{
	std::cout << "����������� ����� \"" << text << "\" ������� ������� ��� ������ ������ ��� ������.\n";
	getline(std::cin, translation);

	return CheckExistenceOfTranslation(text, translation);
}

bool CheckExistenceOfTranslation(const std::string& text, const std::string& translation)
{
	if (translation.empty())
	{
		std::cout << "����� " << text << " ���������������.\n";
		return false;
	}

	return true;
}

void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& translation)
{
	dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, translation));
	std::cout << "����� \"" << wordForTranslation << "\" ��������� � ������� ��� \"" << translation << "\".\n";
}

bool ConfirmSaving()
{
	std::cout << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	if ((userResponse == "y") || (userResponse == "Y"))
	{
		return true;
	}

	std::cout << "��������� �� ����� ���������. �� ��������." << std::endl;

	return false;
}
