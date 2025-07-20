#pragma once
#include <M5Unified.h>

class MonitorInflux {
  private:
    void postData(const String &payload);
    static bool connected;

  public:
    void putLog(const char *format, ...);
    void sendMetric();
};