//
// Created by radek on 27.11.2019.
//

#ifndef ZPR_AGARIO_BLOB_H
#define ZPR_AGARIO_BLOB_H

#include <string>

class Blob {
public:
    Blob(std::basic_string<char> id, std::basic_string<char> x, std::basic_string<char> y, std::basic_string<char> radius);
private:
    std::string _id;
public:
    std::string &getId();

    void setId(std::string &id);

    std::string &getX();

    void setX(std::basic_string<char> x);

    std::string &getY();

    void setY(std::basic_string<char> y);

    std::string &getRadius();

    void setRadius(std::basic_string<char> radius);

private:
    std::string _x;
    std::string _y;
    std::string _radius;
};


#endif //ZPR_AGARIO_BLOB_H
