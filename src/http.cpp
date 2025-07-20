#include <M5Unified.h>
#include <HTTPClient.h>
#include "esp_heap_caps.h"
#include "secrets.hpp"
#include "http.hpp"

void callhttp() {
    HTTPClient http;

    http.begin("https://example.com/");
    int status = http.GET();
    M5.Lcd.print(status);

    http.end();
}
