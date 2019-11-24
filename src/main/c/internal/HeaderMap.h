#pragma once

#include <cctype>
#include <cstring>
#include <string>
#include <unordered_map>

namespace seasocks {

struct CaseInsensitiveHash {
    size_t operator()(const std::string& string) const {
        size_t h = 0;
        for (auto c : string) {
            h = h * 13 + tolower(c);
        }
        return h;
    }
};

struct CaseInsensitiveComparison {
    bool operator()(const std::string& lhs, const std::string& rhs) const {
        return strcasecmp(lhs.c_str(), rhs.c_str()) == 0;
    }
};

using HeaderMap = std::unordered_map<std::string, std::string,
                                     CaseInsensitiveHash, CaseInsensitiveComparison>;

}
