#include <M5Unified.h>
#include <WebServer.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "wifi.hpp"
#include "server.hpp"
#include "monitor.hpp"
#include "http.hpp"
#include "utils/timer.hpp"
#include <SPIFFS.h>

WebServer* server;
MonitorInflux influx;

void setup() {
    M5.begin();
    M5.Lcd.setTextSize(3);

    if (!connectToWiFi()) {
        M5.Lcd.println("failed to connect to the wifi");
        return;
    }
    influx.putLog("connected");

    server = &setupServer(influx);
    server->begin();
    M5.Lcd.println("server started");

    callhttp();



    if (!SPIFFS.begin(true)) {
        M5.Lcd.println("SPIFFS Mount Failed");
        return;
    }
    File root = SPIFFS.open("/");

    if (!root || !root.isDirectory()) {
        M5.Lcd.println("Failed to open");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        M5.Lcd.print(file.name());
        M5.Lcd.print(",");
        file = root.openNextFile();
    }
        SPIFFS.remove("/test.txt");
        SPIFFS.remove("/testaa.txt");

}

Timer metricTimer(10000); // 10秒

void loop() {
    if (server) {
        server->handleClient();
    }
    if (metricTimer.isDue()) {
        influx.sendMetric();
    }
}
