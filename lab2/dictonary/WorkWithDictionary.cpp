#include "stdafx.h"
#include "WorkWithDictionary.h"

bool InteractWithUser(DictionaryMap& dictionary)
{
	bool isRequirePreservation = false;
	const std::string WORD_FOR_EXIT = "...";
	std::cout << "Введите слово чтобы получить его перевод или \"" << WORD_FOR_EXIT << "\" для выхода из программы\n";
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

bool FindAndDisplayTranslation(const DictionaryMap& dictionary, const std::string& searchWord)
{
	bool isWordFound = false;
	auto iterator = dictionary.find(searchWord);
	if (iterator != dictionary.end())
	{
		std::pair<std::string, std::string> pairToDisplay = *iterator;
		std::cout << pairToDisplay.second << "\n";
		isWordFound = true;
	}

	return isWordFound;
}

bool TryToAddNewTranslation(DictionaryMap& dictionary, const std::string& text)
{
	std::cout << "Неизвестное слово \"" << text << "\" Введите перевод или пустую строку для отказа.\n";
	std::string translation;
	getline(std::cin, translation);
	bool isTranslationAdded = RequestTranslation(text, translation);
	if (isTranslationAdded)
	{
		AddTranslationInDictionary(dictionary, text, translation);
	}

	return isTranslationAdded;
}

bool RequestTranslation(const std::string& wordForTranslation, const std::string& translation)
{
	if (!translation.empty())
	{
		std::cout << "Слово \"" << wordForTranslation << "\" сохранено в словаре как \"" << translation << "\".\n";
		return true;
	}
	else
	{
		std::cout << "Слово " << wordForTranslation << " проигнорировано.\n";
		return false;
	}
}

void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& translation)
{
	dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, translation));
}

bool CheckForConfirmationOfSavingDictionary()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	if ((userResponse == "y") || (userResponse == "Y"))
	{
		std::cout << "Изменения сохранены. До свидания." << std::endl;
		return true;
	}

	std::cout << "Изменения не будут сохранены. До свидания." << std::endl;

	return false;
}
