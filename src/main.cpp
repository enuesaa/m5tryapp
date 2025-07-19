#include <M5Unified.h>
#include <WebServer.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "wifi.hpp"
#include "monitor.hpp"
#include "utils/timer.hpp"

WebServer server(80);
MonitorInflux influx;

void handleRoot() {
    IPAddress clientIP = server.client().remoteIP();
    influx.putLog("[ACCESS] IP: %s  URI: /\n", clientIP.toString().c_str());
    server.send(200, "text/plain", "hello!");
}

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(3);

    if (!connectToWiFi()) {
        M5.Lcd.println("failed to connect to the wifi");
        return;
    }
    influx.putLog("connected");

    server.on("/", handleRoot);
    server.begin();
    M5.Lcd.println("server started");
}

Timer metricTimer(10000); // 10秒

void loop() {
    server.handleClient();

    if (metricTimer.isDue()) {
        influx.sendMetric();
    }
}
