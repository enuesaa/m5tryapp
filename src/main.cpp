#include <M5Unified.h>
#include <WebServer.h>

#include "monitor/influx.hpp"
#include "env/runtime.hpp"
#include "utils/timer.hpp"
#include "app/rss.hpp"

namespace influx = monitor::influx;
namespace timer = utils::timer;
namespace runtime = env::runtime;

void setup() {
    if (!runtime::configure()) {
        M5.Lcd.println("failed to configure");
        return;
    }
    influx::putLog("connected");

    app::rss::parse();
}

timer::Timer metricTimer(10000); // 10秒

void loop() {
    if (metricTimer.isDue()) {
        monitor::influx::sendMetric();
    }
}
