//#include "seasocks/PrintfLogger.h"
#include "seasocks/IgnoringLogger.h"
#include "seasocks/Server.h"

#include "lib/sqlite_modern_cpp.h"
#include "GameHandler.cpp"

using namespace seasocks;
using namespace nlohmann;
using namespace sqlite;



int main(int /*argc*/, const char* /*argv*/[]) {
    database db("../../../../agario.db");
    auto logger = std::make_shared<IgnoringLogger>();
    Server server(logger);

    auto handler = std::make_shared<GameHandler>(&server, db);
    server.addWebSocketHandler("/", handler);
    try {
        server.serve("src/agario", 3000);
    }
    catch (sqlite::sqlite_exception& e) {
        std::cerr  << e.get_code() << ": " << e.what() << " during "
                   << e.get_sql() << std::endl;
    }
    return 0;
}
