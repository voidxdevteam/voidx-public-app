#pragma once
#include <string>


#define STR_TO_RGB(str) ((int)strtol(str.c_str(), 0, 16))

int tryParseInt(char *str, int *output, char end);
std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
int count(std::string s, char c);
