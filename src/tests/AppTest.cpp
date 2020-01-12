#define BOOST_TEST_MODULE boost_test_macro_workaround
#include <boost/test/included/unit_test.hpp>
#include <sstream>
#include <string>
#include "../app/c/App.h"
#include "../app/c/App.cpp"
#include "../app/c/Game.cpp"
#include "../app/c/Game.h"
#include "../app/c/Blob.cpp"
#include "../app/c/Blob.h"
#include "../app/c/UserBlob.cpp"
#include "../app/c/UserBlob.h"
#include "../server/c/seasocks/Server.h"
#include "../server/c/seasocks/PrintfLogger.h"
#include "../server/c/seasocks/SynchronousResponse.h"
#include "../server/c/seasocks/SynchronousResponse.cpp"
#include "../server/c/seasocks/ResponseCode.h"
#include "../server/c/seasocks/Connection.h"
#include "../server/c/seasocks/Credentials.h"
#include "../server/c/seasocks/Request.h"
#include "../server/c/seasocks/Request.cpp"
#include "../server/c/seasocks/Response.h"
#include "../server/c/seasocks/ResponseBuilder.h"
#include "../server/c/seasocks/ResponseBuilder.cpp"
#include "../server/c/seasocks/ResponseCode.h"
#include "../server/c/seasocks/ResponseCode.cpp"
#include "../server/c/seasocks/ResponseCodeDefs.h"
#include "../server/c/seasocks/ResponseWriter.h"
#include "../server/c/seasocks/StringUtil.h"
#include "../server/c/seasocks/ToString.h"
#include "../server/c/seasocks/TransferEncoding.h"
#include "../server/c/seasocks/WebSocket.h"
#include "../server/c/seasocks/ZlibContextDisabled.cpp"
#include "../server/c/Connection.cpp"
#include "../server/c/sha1/sha1.h"
#include "../server/c/sha1/sha1.cpp"
#include "../server/c/md5/md5.h"
#include "../server/c/md5/md5.cpp"
#include "../server/c/util/CrackedUri.cpp"
#include "../server/c/util/Json.cpp"
#include "../server/c/util/PathHandler.cpp"
#include "../server/c/util/RootPageHandler.cpp"
#include "../server/c/internal/Base64.h"
#include "../server/c/internal/Base64.cpp"
#include "../server/c/lib/sqlite_modern_cpp.h"
#include "../server/c/lib/sqlite_modern_cpp/log.h"
#include "../server/c/lib/sqlite_modern_cpp/utility/function_traits.h"
#include "../server/c/lib/sqlite_modern_cpp/utility/utf16_utf8.h"

BOOST_AUTO_TEST_CASE( test_app ){
    using namespace seasocks;
    sqlite::database db("./test.db");
    Game game(db);
    auto logger = std::make_shared<PrintfLogger>();
    Server server(logger);
    server.addWebSocketHandler("/", std::make_shared<App>(&server, game));
    server.serve("src/agario", 3000);
//    BOOST_TEST(response["messageType"] == "loggedIn");
}