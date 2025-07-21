#include <M5Unified.h>
#include <WebServer.h>

#include "esp_heap_caps.h"
#include "esp_system.h"
#include "monitor/influx.hpp"
#include "rss.hpp"
#include "server.hpp"
#include "utils/timer.hpp"
#include "wifi.hpp"

WebServer *server;

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    M5.Lcd.setFont(&fonts::efontJA_24);

    if (!connectToWiFi()) {
        M5.Lcd.println("failed to connect to the wifi");
        return;
    }
    monitor::influx::putLog("connected");

    server = &setupServer();
    server->begin();
    M5.Lcd.println("server started");

    parseRSSFeed();
}

utils::timer::Timer metricTimer(10000); // 10秒

void loop() {
    if (server) {
        server->handleClient();
    }
    if (metricTimer.isDue()) {
        monitor::influx::sendMetric();
    }
}
