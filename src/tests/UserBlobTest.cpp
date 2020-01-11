#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "../app/c/UserBlob.cpp"
#include "../app/c/Blob.cpp"

BOOST_AUTO_TEST_CASE( test_get_user_blob_username )
{
    std::string username = "username";
    UserBlob testUserBlob = UserBlob("id", "x", "y", "radius", username);

    std::string blobUsername = testUserBlob.getUsername();

    BOOST_TEST((blobUsername == username ? true : false));
}

BOOST_AUTO_TEST_CASE( test_set_user_blob_username )
{
    UserBlob testUserBlob = UserBlob("id", "x", "y", "radius", "username");

    std::string username = "New username";
    testUserBlob.setUsername(username);

    BOOST_TEST((testUserBlob.getUsername() == username ? true : false));
}
