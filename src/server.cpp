#include "server.hpp"
#include "monitor/influx.hpp"

static WebServer server(80);

void handleRoot() {
    IPAddress clientIP = server.client().remoteIP();
    monitor::influx::putLog("[ACCESS] IP: %s  URI: /\n", clientIP.toString().c_str());
    server.send(200, "text/plain", "hello!");
}

WebServer &setupServer() {
    server.on("/", handleRoot);

    return server;
}
