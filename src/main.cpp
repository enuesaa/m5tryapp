#include <M5Unified.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <WebServer.h>
#include "secrets.h"
#include "esp_heap_caps.h"
#include "esp_system.h"

// https://takagi.blog/m5stack-wifi-get-local-ip-and-global-ip/
// https://yamaccu.github.io/tils/20220808-M5Stack-JSON

WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello!");
}

void printMemoryStats() {
  Serial.println("===== Memory Info =====");
  Serial.printf("Free Heap:                %d bytes\n", esp_get_free_heap_size());
  Serial.printf("Min Ever Free Heap:       %d bytes\n", esp_get_minimum_free_heap_size());
  Serial.printf("Largest Free Block:       %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT));
  Serial.printf("Free PSRAM (if enabled):  %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  Serial.println("========================\n");
}

void setup() {
  Serial.begin(115200);
  M5.begin();
  M5.Lcd.setTextSize(3);
  // M5.setTouchButtonHeight(50);
  // M5.Display.fillRect(0, M5.Display.height() - 50, M5.Display.width() / 3, 50, BLUE);

  Serial.println("start!");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  for (int i = 0; i < 5; i++) {
    if (WiFi.status() == WL_CONNECTED) {
      break;
    }
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("failed. status is ");
    Serial.println(WiFi.status());
    return;
  }
  Serial.println("connected. local ip is ");
  Serial.println(WiFi.localIP());

  printMemoryStats();

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
