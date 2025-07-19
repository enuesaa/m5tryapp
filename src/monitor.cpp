#include <Arduino.h>
#include <HTTPClient.h>
#include "monitor.h"
#include "secrets.h"

void monitor() {
  int heap = esp_get_free_heap_size();

  HTTPClient http;
  http.begin(INFLUX_URL);
  http.addHeader("Authorization", "Token m5tryapp");
  http.addHeader("Content-Type", "text/plain");

  String payload = "mem,device=m5stack heap_free=" + String(heap);
  int status = http.POST(payload);
  Serial.printf("[Influx] Status: %d\n", status);

  http.end();
}

void printMemoryStats() {
  Serial.println("===== Memory Info =====");
  Serial.printf("Free Heap:                %d bytes\n", esp_get_free_heap_size());
  Serial.printf("Min Ever Free Heap:       %d bytes\n", esp_get_minimum_free_heap_size());
  Serial.printf("Largest Free Block:       %d bytes\n", heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT));
  Serial.printf("Free PSRAM (if enabled):  %d bytes\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
  Serial.println("========================\n");
}
