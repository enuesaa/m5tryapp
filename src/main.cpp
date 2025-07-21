#include <M5Unified.h>
#include <WebServer.h>

#include "esp_heap_caps.h"
#include "esp_system.h"
#include "monitor.hpp"
#include "server.hpp"
#include "utils/timer.hpp"
#include "wifi.hpp"
#include "rss.hpp"

WebServer *server;
MonitorInflux influx;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Lcd.setFont(&fonts::efontJA_24);

    if (!connectToWiFi()) {
        M5.Lcd.println("failed to connect to the wifi");
        return;
    }
    influx.putLog("connected");

    server = &setupServer(influx);
    server->begin();
    M5.Lcd.println("server started");

    parseRSSFeed();
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
