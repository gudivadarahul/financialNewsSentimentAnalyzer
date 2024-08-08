#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class SentimentAnalyzer
{
public:
    SentimentAnalyzer();
    double analyzeSentiment(const std::string &text);

private:
    std::unordered_map<std::string, double> sentimentLexicon;
    void loadLexicon();
};