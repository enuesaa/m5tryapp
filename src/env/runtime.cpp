#include "runtime.hpp"
#include "env/network.hpp"
#include <SPIFFS.h>

namespace env::runtime {
    bool configure() {
        auto cfg = M5.config();
        M5.begin(cfg);

        M5.Lcd.setFont(&fonts::efontJA_24);
        M5.Speaker.setVolume(70);

        if (!SPIFFS.begin(true)) {
            M5.Lcd.println("failed to mount SPIFFS");
            return false;
        }
        if (!network::connect()) {
            M5.Lcd.println("failed to connect to the network");
            return false;
        }
        return true;
    };
}; // namespace env::runtime
