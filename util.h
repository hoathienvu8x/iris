#ifndef _UTIL_H
#define _UTIL_H

#include <string>
#include <vector>

namespace iris {
    std::string normalize_sentence(std::string);
    std::vector<std::string> split(std::string);
    std::vector<std::string> load_stopwords(std::string);
    bool is_stopword(std::string, std::vector<std::string>);
    std::vector<std::string> tokenize(std::string, std::vector<std::string>);
}

#endif
