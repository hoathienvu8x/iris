#include <util.h>
#include <fstream>
#include <algorithm>

namespace iris {
    // https://stackoverflow.com/a/25385766
    std::string trim(const std::string base) {
        std::string s(base);
        const char* ws = " \t\n\r\f\v";
        s.erase(0, s.find_first_not_of(ws));
        s.erase(s.find_last_not_of(ws) + 1);
        return s;
    }
    std::string normalize_sentence(const std::string base) {
        std::string s(base);
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
        s = trim(s);
        if (s.length() == 0) return result;
        for(size_t i = 0; i < s.length(); ++i) {
            if ((s.at(i) == ' ' || s.at(i) == '_') && (i - 1 > 0 && (s.at(i - 1) == ' ' || s.at(i - 1) == '_'))) {
                continue;
            }
            result += s.at(i);
        }
        return result;
    }
    // https://stackoverflow.com/a/7408245 (2)
    std::vector<std::string> split(const std::string s) {
        std::vector<std::string> result;
        if (s.length() == 0) return result;
        size_t start = 0, end = 0;
        while ((end = s.find_first_of(" ", start)) != std::string::npos) {
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
    std::vector<std::string> load_stopwords(const std::string filepath) {
        std::vector<std::string> stopwords;
        try {
            std::ifstream ifs(filepath);
            if (ifs) {
                std::string stopword;
                while (ifs >> stopword) {
                    stopword = trim(stopword);
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
    bool is_stopword(const std::string word, const std::vector<std::string> stopwords) {
        if (stopwords.size() == 0) return false;
        return std::binary_search(stopwords.begin(), stopwords.end(), word);
    }
    std::vector<std::string> tokenize(const std::string base, const std::vector<std::string> stopwords) {
        std::string str(base);
        str = normalize_sentence(str);
        std::vector<std::string> tmp = split(str);
        if (stopwords.size() == 0) {
            if(tmp.size() > 0) {
                std::sort(tmp.begin(), tmp.end());
            }
            return tmp;
        }
        std::vector<std::string> tokens;
        for (auto token : tmp) {
            if (!is_stopword(token, stopwords)) tokens.push_back(token);
        }
        if (tokens.size() > 0) {
            std::sort(tokens.begin(), tokens.end());
        }
        return tokens;
    }
    std::string remove_punctuation(const std::string str) {
        const std::string symbols = "@`#$%&~|[]<>'(){}*+-=;,?.!:\"/";
        std::string result = "";
        for(size_t i = 0; i < str.length(); ++i) {
            if (symbols.find(str.at(i)) == std::string::npos) {
                if (result.length() > 0) {
                    if (result.at(result.length() - 1) == ' ' && str.at(i) == ' ') continue;
                }
                result += str.at(i);
            }
        }
        result = trim(result);
        return result;
    }
    std::vector<std::string> word_tokenize(const std::string base, const std::vector<std::string> stopwords) {
        std::string str(base);
        str = normalize_sentence(str);
        str = remove_punctuation(str);
        std::vector<std::string> tmp = split(str);
        if (stopwords.size() == 0) {
            if(tmp.size() > 0) {
                std::sort(tmp.begin(), tmp.end());
            }
            return tmp;
        }
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
