#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

typedef std::map<std::string, std::string> DictionaryMap;

bool CheckTranslationString(const std::string& wordForTranslation, const std::string& translation);
bool InteractWithUser(DictionaryMap& dictionary);
bool FindAndDisplayTranslation(const DictionaryMap& dictionary, const std::string& searchWord);
bool TryToAddNewTranslation(DictionaryMap& dictionary, const std::string& wordForTranslation);
bool CheckForConfirmationOfSavingDictionary();
void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& userResponse);
