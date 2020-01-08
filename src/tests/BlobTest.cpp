#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "../app/c/Blob.cpp"

BOOST_AUTO_TEST_CASE( test_blob_id )
{
    std::string id = "id";
    std::string x = "x";
    std::string y = "y";
    std::string radius = "radius";
    Blob testBlob = Blob(id, x, y, radius);
    std::string blobId = testBlob.getId();
    BOOST_TEST((blobId == id ? true : false));
}