#pragma once
#include <M5Unified.h>

namespace monitor::influx {
    void postData(const String& payload);
void putLog(const char* format, ...);
void sendMetric();
}; // namespace monitor::influx
