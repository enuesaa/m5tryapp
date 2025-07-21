#include "influx.hpp"

#include <HTTPClient.h>
#include <M5Unified.h>
#include "env/vars.hpp"
#include "esp_heap_caps.h"

namespace monitor::influx {

namespace {
  bool connected = true;
}

void postData(const String& payload) {
    if (!connected) return;

    HTTPClient http;
    http.begin(env::vars::INFLUX_URL);
    http.addHeader("Authorization", "Token m5tryapp");
    http.addHeader("Content-Type", "text/plain");

    int status = http.POST(payload);
    connected = (status == 204);

    http.end();
}

void putLog(const char* format, ...) {
    char buf[256];
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);

    String payload = "m5log,device=m5cores3 level=\"info\",message=\"" + String(buf) + "\"";
    postData(payload);
}

void sendMetric() {
    int heap = esp_get_free_heap_size();
    String payload = "mem,device=m5stack heap_free=" + String(heap);
    postData(payload);
}

}  // namespace monitor::influx
