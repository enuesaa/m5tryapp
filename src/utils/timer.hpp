#pragma once

class Timer {
   public:
    Timer(unsigned long interval);
    bool isDue();

   private:
    unsigned long interval;
    unsigned long lastRun;
};
