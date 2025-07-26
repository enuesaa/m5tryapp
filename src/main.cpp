#include <M5Unified.h>
#include <RssParse.hpp>
#include <WebServer.h>

#include "app/rss.hpp"
#include "env/runtime.hpp"
#include "monitor/influx.hpp"
#include "utils/timer.hpp"

namespace influx = monitor::influx;
namespace timer = utils::timer;
namespace runtime = env::runtime;

void setup() {
    hello();

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
