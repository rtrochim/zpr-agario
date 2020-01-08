#ifndef ZPR_AGARIO_BLOB_H
#define ZPR_AGARIO_BLOB_H

#include <string>

class Blob {
public:
    Blob(std::string id, std::string x, std::string y, std::string radius);

    std::string const &getId();

    void setId(std::string id);

    std::string const &getX();

    void setX(std::string x);

    std::string const &getY();

    void setY(std::string y);

    std::string const &getRadius();

    void setRadius(std::string radius);

protected:
    std::string _id;
    std::string _x;
    std::string _y;
    std::string _radius;
};


#endif //ZPR_AGARIO_BLOB_H
