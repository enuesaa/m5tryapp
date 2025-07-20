#include <M5Unified.h>
#include <HTTPClient.h>
#include "esp_heap_caps.h"
#include "secrets.hpp"
#include "http.hpp"
#include <SPIFFS.h>

void callhttp() {
    HTTPClient http;

    http.begin("https://api.openai.com/v1/audio/speech");
    http.addHeader("Authorization", "Bearer " + String(OPENAI_APIKEY));
    http.addHeader("Content-Type", "application/json");

    String payload = R"({
        "model": "gpt-4o-mini-tts",
        "input": "こんにちは！",
        "voice": "shimmer",
        "response_format": "wav"
    })";

    int status = http.POST(payload);
    M5.Lcd.print(status);

    if (status != 200) {
        return;
    }

    if (!SPIFFS.begin(true)) {
        M5.Lcd.println("SPIFFS Mount Failed");
        return;
    }

    File file = SPIFFS.open("/speech.wav", FILE_WRITE);
    if (!file) {
        M5.Lcd.println("Failed to open file for writing");
        return;
    }
    http.writeToStream(&file);
    M5.Lcd.println("Saved");
    file.close();
    http.end();

    File file2 = SPIFFS.open("/speech.wav");
    if (!file2) {
        M5.Lcd.println("Failed to open file");
        return;
    }
    size_t size = file2.size();
    uint8_t* buf = new uint8_t[size];
    file2.read(buf, size);
    file2.close();
    M5.Speaker.playWav(buf, size);

    // see https://zenn.dev/nnn112358/scraps/b3f36dd799e68a
    while (M5.Speaker.isPlaying()) {
        delay(1);
    }
}
