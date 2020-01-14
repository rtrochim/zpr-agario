#ifndef ZPR_AGARIO_BLOB_H
#define ZPR_AGARIO_BLOB_H

#include <string>

/**
 *  @file   Blob.h
 *  @brief  Class representing a single Blob item on the map
 *  @author Radek Trochimiuk & Dominik Ajlert
 *  @date   2019-12-12
 ***********************************************/

class Blob {
public:
    /**
    *  @brief Construct blob object with given id and dimensions.
    *  @param[in]   id   Blob's unique identifier
    *  @param[in]   x   Blob's X coordinate
    *  @param[in]   y   Blob's Y coordinate
    *  @param[in]   radius  Blob's radius
    ************************************************************/
    Blob(std::string id, std::string x, std::string y, std::string radius);

    /**
    *  @brief Retrieve blob  ID
    *  @return  id  Blob identifier
    ************************************************************/
    std::string const &getId() const;

    /**
    *  @brief Set a new ID for the given blob
    *  @param[in]   id  New identifier
    *  @return  Void
    ************************************************************/
    void setId(std::string id);

    /**
    *  @brief Retrieve blob's X coordinate
    *  @return  x  Blob's X coordinate
    ************************************************************/
    std::string const &getX() const;

    /**
    *  @brief Set a new X coordinate for the given blob
    *  @param[in]   x  New X coordinate
    *  @return  void
    ************************************************************/
    void setX(std::string x);

    /**
    *  @brief Retrieve blob's Y coordinate
    *  @return  y  Blob's Y coordinate
    ************************************************************/
    std::string const &getY() const;

    /**
    *  @brief Set a new Y coordinate for the given blob
    *  @param[in]   y  New Y coordinate
    *  @return  void
    ************************************************************/
    void setY(std::string y);

    /**
    *  @brief Retrieve blob's radius
    *  @return  radius  Blob's radius
    ************************************************************/
    std::string const &getRadius() const;

    /**
    *  @brief Set a new radius for the given blob
    *  @param[in]   radius  New radius value
    *  @return  void
    ************************************************************/
    void setRadius(std::string radius);

protected:
    std::string _id; /*!< Blob's unique identifier */
    std::string _x; /*!< X coordinate of a Blob */
    std::string _y; /*!< Y coordinate of a Blob */
    std::string _radius; /*!< Radius of a Blob */
};


#endif //ZPR_AGARIO_BLOB_H
