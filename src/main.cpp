#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "secrets.h"

// https://takagi.blog/m5stack-wifi-get-local-ip-and-global-ip/
// https://yamaccu.github.io/tils/20220808-M5Stack-JSON

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello!");
}

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(3);
  // M5.setTouchButtonHeight(50);
  // M5.Display.fillRect(0, M5.Display.height() - 50, M5.Display.width() / 3, 50, BLUE);

  M5.Lcd.print("start!");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  for (int i = 0; i < 5; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED) {
    M5.Lcd.print("failed. status is ");
    M5.Lcd.println(WiFi.status());
    return;
  }
  M5.Lcd.print("connected. local ip is ");
  M5.Lcd.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  M5.Lcd.println("server started");

  // HTTPClient http;
    
  // http.begin("https://example.com/aaa");
  // int statusCode = http.GET();
  // M5.Lcd.print("status:");
  // M5.Lcd.println(statusCode);

  // http.end();
  // WiFi.disconnect(true);
}

void loop() {
  server.handleClient();  // クライアントからのリクエスト処理

  // M5.delay(1);
  // M5.update();

  // M5.Display.startWrite();
  // if (M5.BtnA.wasClicked()) {
  //   M5.Display.fillRect(0, 0, 50, 50, TFT_RED);
  // }
  // M5.Display.endWrite();
}
