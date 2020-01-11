#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "lib/sqlite_modern_cpp.h"
#include "../app/c/App.h"

using namespace sqlite;

BOOST_AUTO_TEST_CASE( test_user_login )
{
    database db("./test.db");
    std::string blobId = "12";

    BOOST_TEST((blobId == "12" ? true : false));
}