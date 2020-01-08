#ifndef ZPR_AGARIO_USERBLOB_H
#define ZPR_AGARIO_USERBLOB_H

#include "Blob.h"

class UserBlob : public Blob {
public:
    UserBlob(std::string id, std::string x, std::string y, std::string radius, std::string username);

    std::string const &getUsername();

    void setUsername(std::string username);

private:
    std::string _username;
};


#endif //ZPR_AGARIO_USERBLOB_H
