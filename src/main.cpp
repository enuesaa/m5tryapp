#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "secrets.h"

// https://takagi.blog/m5stack-wifi-get-local-ip-and-global-ip/
// https://yamaccu.github.io/tils/20220808-M5Stack-JSON

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
  M5.setTouchButtonHeight(32);

  // M5.Lcd.print("start!");

  // WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // for (int i = 0; i < 5; i++) {
  //   if (WiFi.status() == WL_CONNECTED) {
  //     break;
  //   }
  //   delay(500);
  // }

  // if (WiFi.status() != WL_CONNECTED) {
  //   M5.Lcd.print("failed. status is ");
  //   M5.Lcd.println(WiFi.status());
  //   return;
  // }
  // M5.Lcd.print("connected. local ip is ");
  // M5.Lcd.println(WiFi.localIP());
  
  // HTTPClient http;
    
  // http.begin("https://example.com/aaa");
  // int statusCode = http.GET();
  // M5.Lcd.print("status:");
  // M5.Lcd.println(statusCode);

  // http.end();
  // WiFi.disconnect(true);
}

void loop() {
  M5.delay(1);
  M5.update();

  int w = M5.Display.width() / 5;
  int h = M5.Display.height();
  M5.Display.startWrite();

  if (M5.BtnA.wasClicked()) {
    M5.Display.fillRect(w*1, 0, w-1, h, TFT_RED);
  }
  M5.Display.endWrite();
}
