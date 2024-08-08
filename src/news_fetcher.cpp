#include "news_fetcher.h"
#include <iostream>
#include "rapidjson/document.h"

NewsFetcher::NewsFetcher() : headers(nullptr)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl)
    {
        throw std::runtime_error("Failed to initialize CURL");
    }

    headers = curl_slist_append(headers, "User-Agent: FinancialNewsSentimentAnalyzer/1.0");
}

NewsFetcher::~NewsFetcher()
{
    if (curl)
    {
        curl_easy_cleanup(curl);
    }
    if (headers)
    {
        curl_slist_free_all(headers);
    }
    curl_global_cleanup();
}

std::vector<Article> NewsFetcher::fetchLatestNews(const std::string &apiUrl)
{
    std::string response;

    curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
    {
        throw std::runtime_error("CURL request failed: " + std::string(curl_easy_strerror(res)));
    }

    std::cout << "Raw API Response: " << response << std::endl;

    return parseJsonResponse(response);
}

size_t NewsFetcher::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

std::vector<Article> NewsFetcher::parseJsonResponse(const std::string &jsonResponse)
{
    rapidjson::Document document;
    document.Parse(jsonResponse.c_str());

    std::vector<Article> articles;

    if (document.HasMember("articles") && document["articles"].IsArray())
    {
        const rapidjson::Value &articlesArray = document["articles"];
        for (rapidjson::SizeType i = 0; i < articlesArray.Size(); i++)
        {
            const rapidjson::Value &articleObj = articlesArray[i];
            Article article;

            if (articleObj.HasMember("title") && articleObj["title"].IsString())
                article.title = articleObj["title"].GetString();

            if (articleObj.HasMember("author") && articleObj["author"].IsString())
                article.author = articleObj["author"].GetString();

            if (articleObj.HasMember("description") && articleObj["description"].IsString())
                article.description = articleObj["description"].GetString();

            if (articleObj.HasMember("url") && articleObj["url"].IsString())
                article.url = articleObj["url"].GetString();

            if (articleObj.HasMember("publishedAt") && articleObj["publishedAt"].IsString())
                article.publishedAt = articleObj["publishedAt"].GetString();

            if (articleObj.HasMember("content") && articleObj["content"].IsString())
                article.content = articleObj["content"].GetString();

            std::cout << "Parsed Article:" << std::endl;
            std::cout << "  Title: " << article.title << std::endl;
            std::cout << "  Author: " << article.author << std::endl;
            std::cout << "  Description: " << article.description << std::endl;
            std::cout << "  URL: " << article.url << std::endl;
            std::cout << "  Published At: " << article.publishedAt << std::endl;
            std::cout << "  Content: " << article.content << std::endl;
            std::cout << "------------------------" << std::endl;

            articles.push_back(article);
        }
    }

    return articles;
}