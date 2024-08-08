cmake_minimum_required(VERSION 3.10)
project(FinancialNewsSentimentAnalyzer)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(CURL REQUIRED)
find_package(RapidJSON REQUIRED)

include_directories(${CURL_INCLUDE_DIRS})
include_directories(${RAPIDJSON_INCLUDE_DIRS})

add_executable(FinancialNewsSentimentAnalyzer 
    src/main.cpp
    src/news_fetcher.cpp
    src/text_processor.cpp
)

target_link_libraries(FinancialNewsSentimentAnalyzer ${CURL_LIBRARIES})