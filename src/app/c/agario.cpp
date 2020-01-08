//#include "seasocks/PrintfLogger.h"
#include "seasocks/IgnoringLogger.h"
#include "seasocks/Server.h"

#include "lib/sqlite_modern_cpp.h"
#include "App.h"

int main() {

    Game game(database("../../../../agario.db"));
    Server server(std::make_shared<IgnoringLogger>());
    server.addWebSocketHandler("/", std::make_shared<App>(&server, game));
    server.serve("src/agario", 3000);

    return 0;
}
