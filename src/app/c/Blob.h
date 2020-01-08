#ifndef ZPR_AGARIO_BLOB_H
#define ZPR_AGARIO_BLOB_H

#include <string>

class Blob {

public:
    Blob(std::string id, std::string x, std::string y, std::string radius, std::string username);

    std::string &getId();

    void setId(std::string id);

    std::string &getX();

    void setX(std::string x);

    std::string &getY();

    void setY(std::string y);

    std::string &getRadius();

    void setRadius(std::string radius);

    std::string &getUsername();

    void setUsername(std::string username);

private:
    std::string _id;
    std::string _x;
    std::string _y;
    std::string _radius;
    std::string _username;
};


#endif //ZPR_AGARIO_BLOB_H
