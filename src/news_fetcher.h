#pragma once
#include <string>
#include <vector>
#include <curl/curl.h>

class NewsFetcher {
public:
    NewsFetcher();
    ~NewsFetcher();
    std::vector<std::string> fetchLatestNews(const std::string& apiUrl);

private:
    CURL* curl;
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    struct curl_slist* headers;
};
