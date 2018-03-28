#include "stdafx.h"
#include "WorkWithDictionary.h"

bool InteractWithUser(DictionaryMap& dictionary)
{
	const std::string WORD_FOR_EXIT = "...";
	bool areNewTranslationsAdded = false;
	std::cout << "Введите слово чтобы получить его перевод или \"" << WORD_FOR_EXIT << "\" для выхода из программы\n";
	std::string userResponse;
	while (std::getline(std::cin, userResponse) && (userResponse != WORD_FOR_EXIT))
	{
		if (!FindAndDisplayTranslation(dictionary, userResponse))
		{
			std::string translation;
			if (CheckConsentToAddTranslation(userResponse, translation))
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

bool CheckConsentToAddTranslation(const std::string& text, std::string& translation)
{
	std::cout << "Неизвестное слово \"" << text << "\" Введите перевод или пустую строку для отказа.\n";
	getline(std::cin, translation);

	return CheckTranslationForEmptiness(text, translation);
}

bool CheckTranslationForEmptiness(const std::string& text, const std::string& translation)
{
	if (translation.empty())
	{
		std::cout << "Слово " << text << " проигнорировано.\n";
		return false;
	}

	return true;
}

void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& translation)
{
	dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, translation));
	std::cout << "Слово \"" << wordForTranslation << "\" сохранено в словаре как \"" << translation << "\".\n";
}

bool ConfirmSaving()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	if ((userResponse == "y") || (userResponse == "Y"))
	{
		return true;
	}

	std::cout << "Изменения не будут сохранены. До свидания." << std::endl;

	return false;
}
