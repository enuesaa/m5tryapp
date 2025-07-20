#include <M5Unified.h>
#include <WebServer.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "wifi.hpp"
#include "server.hpp"
#include "monitor.hpp"
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



    if (!SPIFFS.begin(true)) {
        M5.Lcd.println("SPIFFS Mount Failed");
        return;
    }

    if (SPIFFS.exists("/testaa.txt")) {
        M5.Lcd.println("File exists!");
    } else {
        M5.Lcd.println("File not exists!");
        File file = SPIFFS.open("/testaa.txt", FILE_WRITE);
        if (file) {
            file.print("a");
            file.close();
        }
    }
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
