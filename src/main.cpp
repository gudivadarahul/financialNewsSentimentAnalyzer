#include <iostream>
#include "news_fetcher.h"

int main() {
    try {
        NewsFetcher fetcher;
        std::string apiUrl = "https://newsapi.org/v2/top-headlines?country=us&category=business&apiKey=b0892f754bfe40d1af2d4ad7085dbcd6";
        auto news = fetcher.fetchLatestNews(apiUrl);

        std::cout << "Fetched news: " << news[0] << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}