#include <iostream>
#include "news_fetcher.h"

int main() {
    try {
        NewsFetcher fetcher;
        std::string apiUrl = "https://newsapi.org/v2/top-headlines?country=us&category=business&apiKey=b0892f754bfe40d1af2d4ad7085dbcd6";
        auto articles = fetcher.fetchLatestNews(apiUrl);

        std::cout << "Fetched " << articles.size() << " articles:" << std::endl;
        for (const auto& article : articles) {
            std::cout << "Title: " << article.title << std::endl;
            std::cout << "Author: " << article.author << std::endl;
            std::cout << "Description: " << article.description << std::endl;
            std::cout << "URL: " << article.url << std::endl;
            std::cout << "Published At: " << article.publishedAt << std::endl;
            std::cout << "Content: " << article.content << std::endl;
            std::cout << "------------------------" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}