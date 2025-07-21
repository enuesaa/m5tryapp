#include "wifi.hpp"

#include <WiFi.h>

#include "env/vars.hpp"

bool connectToWiFi() {
    WiFi.begin(env::vars::WIFI_SSID, env::vars::WIFI_PASSWORD);
    for (int i = 0; i < 5; ++i) {
        if (WiFi.status() == WL_CONNECTED) {
            return true;
        }
        delay(500);
    }
    return false;
}
