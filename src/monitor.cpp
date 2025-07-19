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

void MonitorInflux::putLog(const char* format, ...) {
    char buf[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    String payload = "m5log,device=m5cores3 level=\"info\",message=\"" + String(buf) + "\"";
    postData(payload);
}

void MonitorInflux::sendMetric() {
    int heap = esp_get_free_heap_size();
    String payload = "mem,device=m5stack heap_free=" + String(heap);
    postData(payload);
}
