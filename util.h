#ifndef _UTIL_H
#define _UTIL_H

#include <string>
#include <vector>
#include <unordered_map>

namespace iris {
    std::string trim(const std::string);
    std::string normalize_sentence(const std::string);
    std::vector<std::string> split(const std::string);
    std::vector<std::string> load_stopwords(const std::string);
    bool is_stopword(const std::string, const std::vector<std::string>);
    std::vector<std::string> tokenize(const std::string, const std::vector<std::string>);
    std::string remove_punctuation(const std::string);
    std::vector<std::string> word_tokenize(const std::string, const std::vector<std::string>);
    std::string convert_html_special_chars(const std::string, const std::unordered_map<std::string, std::string>);
}

#endif
