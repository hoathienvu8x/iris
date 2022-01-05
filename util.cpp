#include <util.h>
#include <fstream>
#include <algorithm>

namespace iris {
    std::string normalize_sentence(std::string s) {
        std::string result = "";
        if (s.length() == 0) return result;
        std::string source[4] = { "…", "“", "”", "" };
        std::string replace[4] = { "...", "\"", "\""," " };
        for(int i = 0; i < 4; ++i) {
            size_t position = s.find(source[i]);
            while (position != std::string::npos) {
                s.replace(position, source[i].length(), replace[i]);
                position = s.find(source[i], position + sizeof(replace[i]));
            }
        }
        const std::string symbols = "@`#$%&~|[]<>'(){}*+-=;,?.!:\"/";
        for(size_t i = 0; i < s.length(); ++i) {
            if (symbols.find(s.at(i)) != std::string::npos) {
                s.insert(i+1, " ");
                s.insert(i, " ");
                i += 2;
            }
        }
        const char* ws = " \t\n\r\f\v";
        s.erase(0, s.find_first_not_of(ws));
        s.erase(s.find_last_not_of(ws) + 1);
        if (s.length() == 0) return result;
        for(size_t i = 0; i < s.length(); ++i) {
            if ((s.at(i) == ' ' || s.at(i) == '_') && (i - 1 > 0 && (s.at(i - 1) == ' ' || s.at(i - 1) == '_'))) {
                continue;
            }
            result += s.at(i);
        }
        return result;
    }
    std::vector<std::string> split(std::string s) {
        std::vector<std::string> result;
        if (s.length() == 0) return result;
        size_t start = 0, end = 0;
        while ((end = s.find_first_of(" _", start)) != std::string::npos) {
            if (end != start) {
                result.push_back(s.substr(start, end - start));
            }
            start = end + 1;
        }
        if (end != start) {
            result.push_back(s.substr(start));
        }
        return result;
    }
    std::vector<std::string> load_stopwords(std::string filepath) {
        std::vector<std::string> stopwords;
        try {
            std::ifstream ifs(filepath);
            if (ifs) {
                const char* ws = " \t\n\r\f\v";
                std::string stopword;
                while (ifs >> stopword) {
                    stopword.erase(0, stopword.find_first_not_of(ws));
                    stopword.erase(stopword.find_last_not_of(ws) + 1);
                    if (stopword.length() > 0) {
                        stopwords.push_back(stopword);
                    }
                }
                ifs.close();
            }
        } catch(...) {}
        if (stopwords.size() > 0) {
            std::sort(stopwords.begin(), stopwords.end());
        }
        return stopwords;
    }
    bool is_stopword(std::string word, std::vector<std::string> stopwords) {
        if (stopwords.size() == 0) return false;
        return std::binary_search(stopwords.begin(), stopwords.end(), word);
    }
    std::vector<std::string> tokenize(std::string str, std::vector<std::string> stopwords) {
        str = normalize_sentence(str);
        std::vector<std::string> tmp = split(str);
        if (stopwords.size() == 0) return tmp;
        std::vector<std::string> tokens;
        for (auto token : tmp) {
            if (!is_stopword(token, stopwords)) tokens.push_back(token);
        }
        if (tokens.size() > 0) {
            std::sort(tokens.begin(), tokens.end());
        }
        return tokens;
    }
}