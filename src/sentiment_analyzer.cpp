#include "sentiment_analyzer.h"
#include "text_processor.h"
#include <fstream>
#include <sstream>
#include <iostream>

SentimentAnalyzer::SentimentAnalyzer()
{
    loadLexicon();
}

void SentimentAnalyzer::loadLexicon()
{
    // Positive words
    sentimentLexicon["rise"] = 1.0;
    sentimentLexicon["up"] = 1.0;
    sentimentLexicon["gain"] = 1.0;
    sentimentLexicon["jump"] = 1.5;
    sentimentLexicon["surge"] = 1.5;
    sentimentLexicon["boost"] = 1.0;
    sentimentLexicon["improve"] = 1.0;
    sentimentLexicon["growth"] = 1.0;
    sentimentLexicon["profit"] = 1.5;
    sentimentLexicon["better"] = 1.0;

    // Negative words
    sentimentLexicon["fall"] = -1.0;
    sentimentLexicon["down"] = -1.0;
    sentimentLexicon["loss"] = -1.5;
    sentimentLexicon["drop"] = -1.0;
    sentimentLexicon["decline"] = -1.0;
    sentimentLexicon["miss"] = -1.0;
    sentimentLexicon["turmoil"] = -1.5;
    sentimentLexicon["bankruptcy"] = -2.0;
    sentimentLexicon["fear"] = -1.0;
    sentimentLexicon["unstable"] = -1.0;

    std::cout << "Loaded " << sentimentLexicon.size() << " words in the sentiment lexicon." << std::endl;
}

double SentimentAnalyzer::analyzeSentiment(const std::string &text)
{
    std::string cleanedText = TextProcessor::cleanText(text);
    std::vector<std::string> tokens = TextProcessor::tokenize(cleanedText);

    double sentimentScore = 0.0;
    int wordCount = 0;

    std::cout << "Analyzing sentiment for text: " << cleanedText << std::endl;
    std::cout << "Tokens: ";
    for (const auto &token : tokens)
    {
        std::cout << token << " ";
        auto it = sentimentLexicon.find(token);
        if (it != sentimentLexicon.end())
        {
            sentimentScore += it->second;
            wordCount++;
            std::cout << "(Score: " << it->second << ") ";
        }
    }
    std::cout << std::endl;

    std::cout << "Total sentiment score: " << sentimentScore << ", Word count: " << wordCount << std::endl;

    // Normalize the score
    double normalizedScore = wordCount > 0 ? sentimentScore / wordCount : 0.0;
    std::cout << "Normalized sentiment score: " << normalizedScore << std::endl;

    return normalizedScore;
}