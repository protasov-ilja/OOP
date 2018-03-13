#pragma once

bool InteractWithUser(std::map<std::string, std::string>& dictionary);
bool FindAndDisplayTranslation(const std::map<std::string, std::string>& dictionary, const std::string& searchWord);
bool CreateNewTranslation(std::map<std::string, std::string>& dictionary, const std::string& wordForTranslation);
bool CheckForConfirmationOfSavingDictionary();
