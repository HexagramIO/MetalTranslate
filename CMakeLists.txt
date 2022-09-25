cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 14)

project(MetalTranslate)

add_library(metaltranslate SHARED src/Translate.h)

set(TARGET_H
        src/Translate.h)

target_sources(metaltranslate PRIVATE src/Translate.cpp)

add_subdirectory(third_party/CTranslate2/)
target_link_libraries(metaltranslate ctranslate2)

add_subdirectory(third_party/Tokenizer/)
target_link_libraries(metaltranslate OpenNMTTokenizer)
