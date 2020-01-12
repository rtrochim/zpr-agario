#ifndef ZPR_AGARIO_USERBLOB_H
#define ZPR_AGARIO_USERBLOB_H

#include "Blob.h"

/**
 *  @file   UserBlob.h
 *  @brief  Class representing a single UserBlob item on the map, derivative of the Blob class
 *  @author Radek Trochimiuk & Dominik Ajlert
 *  @date   2020-01-01
 ***********************************************/

class UserBlob : public Blob {
public:
    /**
    *  @brief Construct a new UserBlob object with given id, dimensions and username.
    *
    *  @param[in]   id   Blob's unique identifier
    *  @param[in]   x   Blob's X coordinate
    *  @param[in]   y   Blob's Y coordinate
    *  @param[in]   radius  Blob's radius
    *  @param[in]   username  Username of a given UserBlob
    ************************************************************/
    UserBlob(std::string id, std::string x, std::string y, std::string radius, std::string username);

    /**
    *  @brief Retrieve username associated with that UserBlob
    *  @return  username  UserBlob's username
    ************************************************************/
    std::string const &getUsername();

    /**
    *  @brief Set a new username for the given UserBlob
    *  @param[in]   username  New username
    *  @return  void
    ************************************************************/
    void setUsername(std::string username);

private:
    std::string _username; /*!< Username associated with a given UserBlob */
};


#endif //ZPR_AGARIO_USERBLOB_H
