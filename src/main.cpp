#include <M5Unified.h>
#include <WebServer.h>
#include "esp_heap_caps.h"
#include "esp_system.h"
#include "wifi.hpp"
#include "server.hpp"
#include "monitor.hpp"
#include "openai.hpp"
#include "utils/timer.hpp"

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

    speech("こんにちは");
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
