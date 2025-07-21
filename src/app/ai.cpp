#include "ai.hpp"

#include <HTTPClient.h>
#include <M5Unified.h>
#include <SPIFFS.h>

#include "env/vars.hpp"

namespace app::ai {
    void speech(const String &text) {
        HTTPClient http;

        http.begin("https://api.openai.com/v1/audio/speech");
        http.addHeader("Authorization", "Bearer " + String(env::vars::OPENAI_APIKEY));
        http.addHeader("Content-Type", "application/json");

        String payload = String("{") + "\"model\": \"gpt-4o-mini-tts\"," + "\"input\": \"" + text + "\"," + "\"voice\": \"shimmer\"," + "\"response_format\": \"wav\"" + "}";

        int status = http.POST(payload);
        if (status != 200) {
            return;
        }
        File file = SPIFFS.open("/speech.wav", FILE_WRITE);
        if (!file) {
            M5.Lcd.println("Failed to open file for writing");
            return;
        }
        http.writeToStream(&file);
        file.close();
        http.end();

        File file2 = SPIFFS.open("/speech.wav");
        if (!file2) {
            M5.Lcd.println("Failed to open file");
            return;
        }
        size_t size = file2.size();
        uint8_t *buf = new uint8_t[size];
        file2.read(buf, size);
        file2.close();

        M5.Speaker.playWav(buf, size);

        while (M5.Speaker.isPlaying()) {
            delay(1);
        }

        if (!SPIFFS.remove("/speech.wav")) {
            M5.Lcd.println("Failed to remove file");
        }
        return;
    }
}; // namespace app::ai
