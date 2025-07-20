#include "wifi.hpp"

#include <WiFi.h>

#include "secrets.hpp"

bool connectToWiFi() {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    for (int i = 0; i < 5; ++i) {
        if (WiFi.status() == WL_CONNECTED) {
            return true;
        }
        delay(500);
    }
    return false;
}
