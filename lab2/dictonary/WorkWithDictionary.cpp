#include "stdafx.h"
#include "WorkWithDictionary.h"

bool InteractWithUser(std::map<std::string, std::string>& dictionary)
{
	bool isNeedSave = false;
	const std::string WORD_FOR_EXIT = "...";
	std::cout << "Введите слово чтобы получить его перевод или \"" << WORD_FOR_EXIT << "\" для выхода из программы\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	while (userResponse != WORD_FOR_EXIT)
	{
		if (!FindAndDisplayTranslation(dictionary, userResponse))
		{
			if (CheckAndCreateNewTranslation(dictionary, userResponse))
			{
				isNeedSave = true;
			}
		}

		getline(std::cin, userResponse);
	}

	if (isNeedSave)
	{
		isNeedSave = CheckForConfirmationOfSavingDictionary();
	}

	return isNeedSave;
}

bool FindAndDisplayTranslation(const std::map<std::string, std::string>& dictionary, const std::string& searchWord)
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

bool CheckAndCreateNewTranslation(std::map<std::string, std::string>& dictionary, const std::string& wordForTranslation)
{
	std::cout << "Неизвестное слово \"" << wordForTranslation << "\" Введите перевод или пустую строку для отказа.\n";
	std::string userResponse;
	getline(std::cin, userResponse);

	return AddWordAndTranslationInDictionary(dictionary, wordForTranslation, userResponse);
}

bool AddWordAndTranslationInDictionary(std::map<std::string, std::string>& dictionary, const std::string& wordForTranslation, const std::string& translation)
{
	if (!translation.empty())
	{
		dictionary.insert(std::pair<std::string, std::string>(wordForTranslation, translation));
		std::cout << "Слово \"" << wordForTranslation << "\" сохранено в словаре как \"" << translation << "\".\n";
		return true;
	}
	else
	{
		std::cout << "Слово " << wordForTranslation << " проигнорировано.\n";
		return false;
	}
}

bool CheckForConfirmationOfSavingDictionary()
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string userResponse;
	getline(std::cin, userResponse);
	std::transform(userResponse.begin(), userResponse.end(), userResponse.begin(), ::tolower);
	if (userResponse == "y")
	{
		std::cout << "Изменения сохранены. До свидания." << std::endl;
		return true;
	}

	std::cout << "Изменения не будут сохранены. До свидания." << std::endl;

	return false;
}
