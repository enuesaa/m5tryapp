#include <HTTPClient.h>
#include "esp_heap_caps.h"
#include "monitor.hpp"
#include "secrets.hpp"

void MonitorInflux::postData(const String& payload) {
    HTTPClient http;
    http.begin(INFLUX_URL);
    http.addHeader("Authorization", "Token m5tryapp");
    http.addHeader("Content-Type", "text/plain");

    int status = http.POST(payload);
    Serial.printf("[MonitorInflux] Status: %d\n", status);

    http.end();
}

void MonitorInflux::putLog(const String& message) {
    String payload = "m5log,device=m5cores3 level=\"info\",message=\"" + message + "\"";
    postData(payload);
}

void MonitorInflux::sendMetrics() {
    int heap = esp_get_free_heap_size();
    String payload = "mem,device=m5stack heap_free=" + String(heap);
    postData(payload);
}
