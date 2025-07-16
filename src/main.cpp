#include <M5Unified.h>
#include <WiFi.h>
#include "secrets.h"

// https://takagi.blog/m5stack-wifi-get-local-ip-and-global-ip/
// https://yamaccu.github.io/tils/20220808-M5Stack-JSON

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
  M5.Lcd.print("start!");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int retryCount = 0;
  while (WiFi.status() != WL_CONNECTED && retryCount < 5) {
    delay(500);
    retryCount++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    M5.Lcd.print("connected");
    WiFi.disconnect(true);
  } else {
    M5.Lcd.print("failed");
      M5.Lcd.print("status:");
  M5.Lcd.println(WiFi.status());
  }
}

void loop() {}
