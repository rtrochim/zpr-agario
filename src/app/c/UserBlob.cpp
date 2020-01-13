//
// Created by radek on 08.01.2020.
//

#include "UserBlob.h"

UserBlob::UserBlob(std::string id, std::string x, std::string y, std::string radius, std::string username)
: Blob(std::move(id), std::move(x), std::move(y), std::move(radius)), _username(std::move(username)) {}

std::string const &UserBlob::getUsername() const {
    return _username;
}

void UserBlob::setUsername(std::string username) {
    _username = std::move(username);
}
