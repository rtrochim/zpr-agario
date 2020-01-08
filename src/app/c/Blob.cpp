#include "Blob.h"

Blob::Blob(std::string id, std::string x, std::string y, std::string radius, std::string username)
: _id(std::move(id)), _x(std::move(x)), _y(std::move(y)), _radius(std::move(radius)), _username(std::move(username)){}

std::string &Blob::getId(){
    return _id;
}

void Blob::setId(std::string id) {
    _id = std::move(id);
}

std::string &Blob::getX(){
    return _x;
}

void Blob::setX(std::string x) {
    _x = std::move(x);
}

std::string &Blob::getY(){
    return _y;
}

void Blob::setY(std::string y) {
    _y = std::move(y);
}

std::string &Blob::getRadius(){
    return _radius;
}

void Blob::setRadius(std::string radius) {
    _radius = std::move(radius);
}

std::string &Blob::getUsername(){
    return _username;
}

void Blob::setUsername(std::string username) {
    _username = std::move(username);
}
