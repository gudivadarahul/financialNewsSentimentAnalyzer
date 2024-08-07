#include <iostream>
#include <boost/version.hpp>
#include <curl/curl.h>
#include "rapidjson/document.h"

int main() {
    std::cout << "Hello, Financial News Sentiment Analyzer!" << std::endl;
    std::cout << "Boost version: " << BOOST_VERSION << std::endl;
    std::cout << "libcurl version: " << curl_version() << std::endl;
    std::cout << "RapidJSON version: " << RAPIDJSON_VERSION_STRING << std::endl;
    return 0;
}