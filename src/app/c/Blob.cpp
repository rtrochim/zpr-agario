//
// Created by radek on 27.11.2019.
//

#include "Blob.h"

Blob::Blob(std::basic_string<char> id, std::basic_string<char> x, std::basic_string<char> y, std::basic_string<char> radius) : _id(id), _x(x), _y(y), _radius(radius){}

std::string &Blob::getId(){
    return _id;
}

void Blob::setId(std::string &id) {
    _id = id;
}

std::string &Blob::getX(){
    return _x;
}

void Blob::setX(std::basic_string<char> x) {
    _x = x;
}

std::string &Blob::getY(){
    return _y;
}

void Blob::setY(std::basic_string<char> y) {
    _y = y;
}

std::string &Blob::getRadius(){
    return _radius;
}

void Blob::setRadius(std::basic_string<char> radius) {
    _radius = radius;
}