#include "server.hpp"

static WebServer server(80);
static MonitorInflux *monitor = nullptr;

void handleRoot() {
    IPAddress clientIP = server.client().remoteIP();
    monitor->putLog("[ACCESS] IP: %s  URI: /\n", clientIP.toString().c_str());
    server.send(200, "text/plain", "hello!");
}

WebServer &setupServer(MonitorInflux &influx) {
    monitor = &influx;
    server.on("/", handleRoot);

    return server;
}
