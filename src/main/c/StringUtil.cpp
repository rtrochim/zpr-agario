#include "seasocks/StringUtil.h"

#include <cctype>
#include <cerrno>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <algorithm>

namespace seasocks {

char* skipWhitespace(char* str) {
    while (isspace(*str)) {
        ++str;
    }
    return str;
}

char* skipNonWhitespace(char* str) {
    while (*str && !isspace(*str)) {
        ++str;
    }
    return str;
}

char* shift(char*& str) {
    if (str == nullptr) {
        return nullptr;
    }
    char* startOfWord = skipWhitespace(str);
    if (*startOfWord == 0) {
        str = startOfWord;
        return nullptr;
    }
    char* endOfWord = skipNonWhitespace(startOfWord);
    if (*endOfWord != 0) {
        *endOfWord++ = 0;
    }
    str = endOfWord;
    return startOfWord;
}

std::string trimWhitespace(const std::string& str) {
    auto l = [](const auto& c) { return std::isspace(c); };
    const auto start = std::find_if_not(str.begin(), str.end(), l);
    const auto end = std::find_if_not(str.rbegin(), str.rend(), l).base();

    return (start < end ? std::string(start, end) : "");
}

std::string getLastError() {
    char errbuf[1024];
    const auto ignore = strerror_r(errno, errbuf, sizeof(errbuf));
    static_cast<void>(ignore);
    return errbuf;
}

std::string formatAddress(const sockaddr_in& address) {
    char ipBuffer[24];
    sprintf(ipBuffer,
            "%d.%d.%d.%d:%d",
            (address.sin_addr.s_addr >> 0) & 0xff,
            (address.sin_addr.s_addr >> 8) & 0xff,
            (address.sin_addr.s_addr >> 16) & 0xff,
            (address.sin_addr.s_addr >> 24) & 0xff,
            htons(address.sin_port));
    return ipBuffer;
}

std::vector<std::string> split(const std::string& input, char splitChar) {
    if (input.empty()) {
        return {};
    }

    std::vector<std::string> result;
    size_t pos = 0;
    size_t newPos;
    while ((newPos = input.find(splitChar, pos)) != std::string::npos) {
        result.push_back(input.substr(pos, newPos - pos));
        pos = newPos + 1;
    }
    result.push_back(input.substr(pos));
    return result;
}

void replace(std::string& string, const std::string& find, const std::string& replace) {
    if (find.empty()) {
        return;
    }

    size_t pos = 0;
    const size_t findLen = find.length();
    const size_t replaceLen = replace.length();
    while ((pos = string.find(find, pos)) != std::string::npos) {
        string = string.substr(0, pos) + replace + string.substr(pos + findLen);
        pos += replaceLen;
    }
}

bool caseInsensitiveSame(const std::string& lhs, const std::string& rhs) {
    return strcasecmp(lhs.c_str(), rhs.c_str()) == 0;
}

std::string webtime(time_t time) {
    struct tm timeValue;
    gmtime_r(&time, &timeValue);
    char buf[1024];
    // Wed, 20 Apr 2011 17:31:28 GMT
    strftime(buf, sizeof(buf) - 1, "%a, %d %b %Y %H:%M:%S %Z", &timeValue);
    return buf;
}

std::string now() {
    return webtime(time(nullptr));
}

}
