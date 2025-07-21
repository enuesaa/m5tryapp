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

/*
Example:

WebServer *server;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Lcd.setFont(&fonts::efontJA_24);

    if (!connectToWiFi()) {
        M5.Lcd.println("failed to connect to the wifi");
        return;
    }
    server = &setupServer();
    server->begin();
    M5.Lcd.println("server started");
}

void loop() {
    if (server) {
        server->handleClient();
    }
}
*/