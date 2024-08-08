#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>
#include "rapidjson/document.h"

struct Article {
    std::string title;
    std::string author;
    std::string description;
    std::string url;
    std::string publishedAt;
    std::string content;
};

class NewsFetcher {
public:
    NewsFetcher();
    ~NewsFetcher();
    std::vector<Article> fetchLatestNews(const std::string& apiUrl);

private:
    CURL* curl;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    struct curl_slist* headers;
    std::vector<Article> parseJsonResponse(const std::string& jsonResponse);
};