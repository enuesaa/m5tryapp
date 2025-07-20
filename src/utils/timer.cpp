#include "timer.hpp"

#include <M5Unified.h>

Timer::Timer(unsigned long interval) : interval(interval), lastRun(0) {}

bool Timer::isDue() {
    unsigned long now = millis();
    if (now - lastRun >= interval) {
        lastRun = now;
        return true;
    }
    return false;
}
