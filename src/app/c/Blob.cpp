#include "Blob.h"

Blob::Blob(std::string id, std::string x, std::string y, std::string radius)
: _id(std::move(id)), _x(std::move(x)), _y(std::move(y)), _radius(std::move(radius)){}

std::string const &Blob::getId() const {
    return _id;
}

void Blob::setId(std::string id) {
    _id = std::move(id);
}

std::string const &Blob::getX() const {
    return _x;
}

void Blob::setX(std::string x) {
    _x = std::move(x);
}

std::string const &Blob::getY() const {
    return _y;
}

void Blob::setY(std::string y) {
    _y = std::move(y);
}

std::string const &Blob::getRadius() const {
    return _radius;
}

void Blob::setRadius(std::string radius) {
    _radius = std::move(radius);
}
