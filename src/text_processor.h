#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <regex>
#include <sstream>

class TextProcessor
{
public:
    static std::string cleanText(const std::string &text);
    static std::vector<std::string> tokenize(const std::string &text);
    static std::string removeStopWords(const std::string &text);

private:
    static const std::vector<std::string> stopWords;
};
