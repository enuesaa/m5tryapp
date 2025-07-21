#include <WiFi.h>

#include "env/vars.hpp"
#include "network.hpp"

namespace env::network {
    bool connect() {
        WiFi.begin(env::vars::WIFI_SSID, env::vars::WIFI_PASSWORD);
        for (int i = 0; i < 5; ++i) {
            if (WiFi.status() == WL_CONNECTED) {
                return true;
            }
            delay(500);
        }
        return false;
    };
}; // namespace network::wifi
