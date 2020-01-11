#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "../app/c/Blob.cpp"

BOOST_AUTO_TEST_CASE( test_get_blob_id )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobId = testBlob.getId();

    BOOST_TEST((blobId == id ? true : false));
}

BOOST_AUTO_TEST_CASE( test_set_blob_id )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobId = "New id";
    testBlob.setId(blobId);

    BOOST_TEST((testBlob.getId() == blobId ? true : false));
}

BOOST_AUTO_TEST_CASE( test_get_blob_x )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobX = testBlob.getX();

    BOOST_TEST((blobX == x ? true : false));
}

BOOST_AUTO_TEST_CASE( test_set_blob_x )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobX = "New X";
    testBlob.setX(blobX);

    BOOST_TEST((testBlob.getX() == blobX ? true : false));
}

BOOST_AUTO_TEST_CASE( test_get_blob_y )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobY = testBlob.getY();

    BOOST_TEST((blobY == y ? true : false));
}

BOOST_AUTO_TEST_CASE( test_set_blob_y )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobY = "New Y";
    testBlob.setY(blobY);

    BOOST_TEST((testBlob.getY() == blobY ? true : false));
}

BOOST_AUTO_TEST_CASE( test_get_blob_radius )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobRadius = testBlob.getRadius();

    BOOST_TEST((blobRadius == radius ? true : false));
}

BOOST_AUTO_TEST_CASE( test_set_blob_radius )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);

    std::string blobRadius = "New radius";
    testBlob.setRadius(blobRadius);

    BOOST_TEST((testBlob.getRadius() == blobRadius ? true : false));
}