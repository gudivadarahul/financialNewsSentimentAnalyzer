#include "text_processor.h"
#include <iostream>

const std::vector<std::string> TextProcessor::stopWords = {
    "a", "an", "and", "are", "as", "at", "be", "by", "for", "from",
    "has", "he", "in", "is", "it", "its", "of", "on", "that", "the",
    "to", "was", "were", "will", "with"};

std::string TextProcessor::cleanText(const std::string &text)
{
    std::string cleaned = text;

    // Convert to lowercase
    std::transform(cleaned.begin(), cleaned.end(), cleaned.begin(),
                   [](unsigned char c)
                   { return std::tolower(c); });

    // Remove URLs
    cleaned = std::regex_replace(cleaned, std::regex(R"((https?://[^\s]+))"), "");

    // Remove special characters and numbers
    cleaned = std::regex_replace(cleaned, std::regex("[^a-z\\s]"), "");

    // Remove extra whitespace
    cleaned = std::regex_replace(cleaned, std::regex("\\s+"), " ");

    return cleaned;
}

std::vector<std::string> TextProcessor::tokenize(const std::string &text)
{
    std::vector<std::string> tokens;
    std::istringstream iss(text);
    std::string token;
    while (iss >> token)
    {
        tokens.push_back(token);
    }
    return tokens;
}

std::string TextProcessor::removeStopWords(const std::string &text)
{
    std::vector<std::string> tokens = tokenize(text);
    tokens.erase(
        std::remove_if(tokens.begin(), tokens.end(),
                       [](const std::string &token)
                       {
                           return std::find(stopWords.begin(), stopWords.end(), token) != stopWords.end();
                       }),
        tokens.end());

    std::string result;
    for (const auto &token : tokens)
    {
        result += token + " ";
    }
    return result;
}