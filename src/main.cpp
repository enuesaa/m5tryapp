#include <M5Unified.h>
#include <WebServer.h>

#include "esp_heap_caps.h"
#include "esp_system.h"
#include "monitor/influx.hpp"
#include "env/runtime.hpp"
#include "utils/timer.hpp"

namespace influx = monitor::influx;
namespace timer = utils::timer;
namespace runtime = env::runtime;

void setup() {
    if (!runtime::configure()) {
        M5.Lcd.println("failed to connect to the network");
        return;
    }
    influx::putLog("connected");

    // parseRSSFeed();
}

timer::Timer metricTimer(10000); // 10秒

void loop() {
    if (metricTimer.isDue()) {
        monitor::influx::sendMetric();
    }
}
