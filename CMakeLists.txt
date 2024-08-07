cmake_minimum_required(VERSION 3.10)
project(FinancialNewsSentimentAnalyzer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED)
find_package(CURL REQUIRED)
find_package(RapidJSON REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${RAPIDJSON_INCLUDE_DIRS})

add_executable(FinancialNewsSentimentAnalyzer src/main.cpp)

target_link_libraries(FinancialNewsSentimentAnalyzer ${Boost_LIBRARIES} ${CURL_LIBRARIES})