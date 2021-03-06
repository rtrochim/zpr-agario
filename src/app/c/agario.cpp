#include "seasocks/PrintfLogger.h"
#include "seasocks/IgnoringLogger.h"
#include "seasocks/Server.h"

#include "lib/sqlite_modern_cpp.h"
#include "App.h"

int main() {
    // Initialize game and database
    Game game(database("../../../../agario.db"));

    // Initialize server, add handler for WebSocket communication and serve static files from directory
    Server server(std::make_shared<PrintfLogger>());
    server.addWebSocketHandler("/", std::make_shared<App>(&server, game));
    server.serve("src/agario", 3000);

    return 0;
}
