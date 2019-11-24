#pragma once

#include <sstream>
#include <string>
#include <type_traits>

namespace seasocks {

template <typename T, typename std::enable_if<!std::is_integral<typename std::decay<T>::type>::value, int>::type = 0>
std::string toString(const T& obj) {
    std::stringstream str;
    str.imbue(std::locale("C"));
    str << obj;
    return str.str();
}

template <typename T, typename std::enable_if<std::is_integral<typename std::decay<T>::type>::value, int>::type = 0>
inline std::string toString(T&& value) {
    return std::to_string(std::forward<T>(value));
}

inline std::string toString(const char* str) {
    return str;
}

inline std::string toString(const std::string& str) {
    return str;
}

inline std::string toString(char c) {
    return std::string(1, c);
}

}
