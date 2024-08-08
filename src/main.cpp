#include <iostream>
#include "news_fetcher.h"
#include "text_processor.h"
#include "sentiment_analyzer.h"

int main()
{
    try
    {
        NewsFetcher fetcher;
        SentimentAnalyzer analyzer;
        std::string apiUrl = "https://newsapi.org/v2/top-headlines?country=us&category=business&apiKey=b0892f754bfe40d1af2d4ad7085dbcd6";
        auto articles = fetcher.fetchLatestNews(apiUrl);

        std::cout << "Fetched " << articles.size() << " articles:" << std::endl;
        for (const auto &article : articles)
        {
            std::cout << "Title: " << article.title << std::endl;
            std::cout << "Author: " << article.author << std::endl;
            std::cout << "Description: " << article.description << std::endl;

            std::string textToAnalyze = article.content;
            if (textToAnalyze.empty())
            {
                textToAnalyze = article.description;
                if (textToAnalyze.empty())
                {
                    textToAnalyze = article.title;
                }
            }

            std::cout << "Text to analyze: " << textToAnalyze << std::endl;

            std::string cleanedContent = TextProcessor::cleanText(textToAnalyze);
            std::cout << "Cleaned Content: " << cleanedContent << std::endl;

            std::string processedContent = TextProcessor::removeStopWords(cleanedContent);
            std::cout << "Processed Content: " << processedContent << std::endl;

            double sentiment = analyzer.analyzeSentiment(processedContent);

            std::cout << "Sentiment Score: " << sentiment << std::endl;
            std::cout << "Sentiment: " << (sentiment > 0.2 ? "Positive" : (sentiment < -0.2 ? "Negative" : "Neutral")) << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}