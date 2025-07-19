#pragma once

class MonitorInflux {
private:
    void postData(const String& payload);

public:
    void putLog(const char* format, ...);
    void sendMetric();
};