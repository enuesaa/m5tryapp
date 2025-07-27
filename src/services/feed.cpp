#include "feed.hpp"
#include "env/vars.hpp"
#include "services/ai.hpp"
#include <HTTPClient.h>
#include <M5Unified.h>
#include <Rss.h>
#include <ArduinoJson.h>

namespace services::feed {
    void parse() {
        HTTPClient http;
        http.begin(env::vars::RSS_FEED_URI);

        int code = http.GET();
        if (code != 200) {
            M5.Lcd.printf("HTTP Error: %d\n", code);
            return;
        }
        http.end();

        String body = http.getString();

        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, body);

        if (error) {
            M5.Display.println("JSON parse error");
            return;
        }

        String inputheader = "この AWS NEWS を日本語で20文字程度にまとめて。不要な文言は出力しないで。";
        JsonArray items = doc["items"];

        for (JsonObject item : items) {
            const char* title = item["title"];
            const char* description = item["description"];
            String input = inputheader + title + ".\n" + description;
            String output = services::ai::chat(input);
            M5.Display.println(output);
            services::ai::speech(output);
        }
    }
}; // namespace services::feed
