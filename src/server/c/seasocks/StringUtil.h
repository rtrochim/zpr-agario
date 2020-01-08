#pragma once

#include <netinet/in.h>

#include <ctime>
#include <string>
#include <vector>

namespace seasocks {

char* skipWhitespace(char* str);
char* skipNonWhitespace(char* str);
char* shift(char*& str);
std::string trimWhitespace(const std::string& str);

std::string getLastError();
std::string formatAddress(const sockaddr_in& address);

std::vector<std::string> split(const std::string& input, char splitChar);

void replace(std::string& string, const std::string& find, const std::string& replace);

bool caseInsensitiveSame(const std::string& lhs, const std::string& rhs);

std::string webtime(time_t time);

std::string now();


} // namespace zpr-agario
