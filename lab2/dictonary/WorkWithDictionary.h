#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string>

typedef std::map<std::string, std::string> DictionaryMap;

bool InteractWithUser(DictionaryMap& dictionary);
bool FindAndDisplayTranslation(const DictionaryMap& dictionary, const std::string& searchWord);
bool ConfirmTranslationAdding(const std::string& text, std::string& translation);
bool CheckExistenceOfTranslation(const std::string& text, const std::string& translation);
bool ConfirmSaving();
void AddTranslationInDictionary(DictionaryMap& dictionary, const std::string& wordForTranslation, const std::string& userResponse);
