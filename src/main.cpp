#include <M5Unified.h>
#include <Rss.hpp>

#include "env/runtime.hpp"
#include "monitor/influx.hpp"
#include "utils/timer.hpp"
#include "services/feed.hpp"

namespace influx = monitor::influx;
namespace timer = utils::timer;
namespace runtime = env::runtime;

void setup() {
    if (!runtime::configure()) {
        M5.Lcd.println("failed to configure");
        return;
    }
    influx::putLog("connected");

    services::feed::parse();
}

timer::Timer metricTimer(10000); // 10秒

void loop() {
    if (metricTimer.isDue()) {
        monitor::influx::sendMetric();
    }
}
