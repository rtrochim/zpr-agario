#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "lib/sqlite_modern_cpp.h"
#include "lib/json.hpp"
#include "../app/c/App.h"
#include "../app/c/Game.cpp"
#include "../app/c/Blob.cpp"
#include "../app/c/UserBlob.cpp"

using namespace nlohmann;

Game game(database("./test.db"));

BOOST_AUTO_TEST_CASE( test_new_user_login )
{
    json payload;
    json response;

    payload["id"] = "id";
    payload["x"] = "x";
    payload["y"] = "y";
    payload["r"] = "20";
    payload["width"] = 900;
    payload["height"] = 1400;
    payload["username"] = "username";

    game.login(payload, response);
    BOOST_TEST(response["messageType"] == "loggedIn");
}

BOOST_AUTO_TEST_CASE( test_new_user_login_2 )
{
    json payload;
    json response;

    payload["id"] = "id2";
    payload["x"] = "x2";
    payload["y"] = "y2";
    payload["r"] = "12";
    payload["width"] = 900;
    payload["height"] = 1400;
    payload["username"] = "username2";

    game.login(payload, response);
    BOOST_TEST(response["messageType"] == "loggedIn");
}

BOOST_AUTO_TEST_CASE( test_user_eats_game_blob )
{
    json payload;
    json response;

    payload["blobId"] = "id";
    payload["id"] = "id";
    payload["gameBlobId"] = 10;
    payload["username"] = "username";

    game.eatGameBlob(payload, response);
    BOOST_TEST(response["messageType"] == "update");
    BOOST_TEST(response["score"] == 1);
}

BOOST_AUTO_TEST_CASE( test_user_update )
{
    json payload;
    json response;

    payload["id"] = "id";
    payload["x"] = "x";
    payload["y"] = "y";
    payload["r"] = "20";
    payload["username"] = "username";

    game.update(payload, response);
    BOOST_TEST(response["messageType"] == "update");
    BOOST_TEST(response["score"] == 1);
}

BOOST_AUTO_TEST_CASE( test_user_eats_user_blob )
{
    json payload;
    json response;

    payload["id"] = "id";
    payload["userBlobId"] = "id2";

    game.eatUserBlob(payload, response);
    BOOST_TEST(response["messageType"] == "update");
    BOOST_TEST(response["score"] == 13);
}

BOOST_AUTO_TEST_CASE( test_user_logout )
{
    json payload;

    payload["id"] = "id";
    payload["username"] = "username";

    game.logout(payload);
}

BOOST_AUTO_TEST_CASE( test_existing_user_login )
{
    json payload;
    json response;

    payload["id"] = "id";
    payload["x"] = "x";
    payload["y"] = "y";
    payload["r"] = "r";
    payload["width"] = 900;
    payload["height"] = 1400;
    payload["username"] = "username";

    game.login(payload, response);
    BOOST_TEST(response["messageType"] == "loggedIn");
    BOOST_TEST(response["highscore"] == 13);
}