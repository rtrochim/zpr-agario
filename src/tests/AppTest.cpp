#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "../app/c/App.cpp"
#include "../app/c/Game.cpp"
#include "../app/c/Blob.cpp"
#include "../app/c/UserBlob.cpp"
#include "../server/c/seasocks/Server.h"
#include "../server/c/seasocks/PrintfLogger.h"

database db("./test.db");
Game game(db);

BOOST_AUTO_TEST_CASE( test_app )
{
    Server server(std::make_shared<PrintfLogger>());
    server.addWebSocketHandler("/", std::make_shared<App>(&server, game));
    // server.serve("src/agario", 3000);
    // BOOST_TEST(response["messageType"] == "loggedIn");
}